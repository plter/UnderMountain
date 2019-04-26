/*
 * @file webserver.c
 * @author Akagi201
 * @date 2015/01/03
 * @editor plter at 20190425
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> // _SC_NPROCESSORS_ONLN on OS X
#include <uv.h>
#include <uv_boot/http_parser.h>
#include <uv_boot/http_server.h>

#define HTTP_PORT (8000)
#define MAX_WRITE_HANDLES (1000)
#define INDEX_HTML "index.html"

#define HTTP_HEADER "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/html\r\n" \
    "\r\n"

#define UV_ERR(err, msg) fprintf(stderr,"%s: [%s(%d): %s]\n", msg, uv_err_name((err)), (int)err, uv_strerror((err)))

#define UV_CHECK(err, msg) \
do { \
  if (err != 0) { \
    UV_ERR(err, msg); \
    exit(1); \
  } \
} while(0)

static uv_loop_t *uv_loop;
static uv_tcp_t server;
static http_parser_settings parser_settings;

void on_close(uv_handle_t *handle) {

    http_request_t *http_request = (http_request_t *) handle->data;

    printf("connection closed\n");

    if (NULL != http_request) {
        free(http_request);
        http_request = NULL;
    }

    return;
}

void alloc_cb(uv_handle_t *handle/*handle*/, size_t suggested_size, uv_buf_t *buf) {
    *buf = uv_buf_init((char *) malloc(suggested_size), (unsigned int) suggested_size);

    return;
}

void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
    ssize_t parsed = 0;
    printf("on read, nread: %ld\n", nread);

    /* get back our http request*/
    http_request_t *http_request = stream->data;

    if (nread >= 0) {
        /*  call our http parser on the received tcp payload */
        parsed = (ssize_t) http_parser_execute(
                &http_request->parser, &parser_settings, buf->base, (size_t) nread);
        if (parsed < nread) {
            fprintf(stderr, "parse error");
            uv_close((uv_handle_t *) &http_request->client, on_close);
        }
    } else {
        if (nread != UV_EOF) {
            UV_ERR(nread, "Read error");
        }
        uv_close((uv_handle_t *) &http_request->client, on_close);
    }

    if (NULL != buf->base) {
        free(buf->base);
    }

    return;
}

/**
* Initializes default values, counters.
*/
int on_message_begin(http_parser *parser/*parser*/) {
    printf("***MESSAGE BEGIN***");
    http_request_t *http_request = parser->data;
    http_request->header_lines = 0;

    return 0;
}

/**
* Extract the method name.
*/
int on_headers_complete(http_parser *parser/*parser*/) {
    printf("***HEADERS COMPLETE***");

    http_request_t *http_request = parser->data;

    const char *method = http_method_str((enum http_method) parser->method);

    http_request->method = malloc(sizeof(method));
    strncpy(http_request->method, method, strlen(method));

    return 0;
}

/**
* Copies url string to http_request->url.
*/
int on_url(http_parser *parser/*parser*/, const char *at, size_t length) {
    printf("Url: %.*s", (int) length, at);

    http_request_t *http_request = parser->data;

    http_request->url = malloc(length + 1);

    strncpy(http_request->url, at, length);

    http_request->url[length] = '\0';

    return 0;
}

/**
* Copy the header field name to the current header item.
*/
int on_header_field(http_parser *parser/*parser*/, const char *at, size_t length) {
    printf("Header field: %.*s", (int) length, at);

    http_request_t *http_request = parser->data;

    http_header_t *header = &http_request->headers[http_request->header_lines];

    header->field = malloc(length + 1);
    header->field_length = length;

    strncpy(header->field, at, length);

    header->field[length] = '\0';

    return 0;
}

/**
* Now copy its assigned value.
*/
int on_header_value(http_parser *parser/*parser*/, const char *at, size_t length) {
    printf("Header value: %.*s", (int) length, at);

    http_request_t *http_request = parser->data;

    http_header_t *header = &http_request->headers[http_request->header_lines];

    header->value = malloc(length + 1);
    header->value_length = length;

    strncpy(header->value, at, length);

    header->value[length] = '\0';

    ++http_request->header_lines;

    return 0;
}

int on_body(http_parser *parser/*parser*/, const char *at, size_t length) {
    printf("Body: %.*s", (int) length, at);
    http_request_t *http_request = parser->data;

    http_request->body = malloc(length + 1);
    http_request->body_length = length;

    strncpy(http_request->body, at, length);

    http_request->body[length] = '\0';

    return 0;
}

/**
* Closes current tcp socket after write.
*/
void on_put_write(uv_write_t *req, int status) {
    int i = 0;
    http_header_t *header = NULL;
    http_request_t *http_request = req->data;

    UV_CHECK(status, "on_put_write");

    if (http_request->url != NULL) {
        free(http_request->url);
        http_request->url = NULL;
    }

    if (http_request->body != NULL) {
        free(http_request->body);
        http_request->body = NULL;
    }

    if (http_request->method != NULL) {
        free(http_request->method);
        http_request->method = NULL;
    }

    for (i = 0; i < http_request->header_lines; ++i) {
        header = &http_request->headers[i];
        if (header->field != NULL) {
            free(header->field);
            header->field = NULL;
        }
        if (header->value != NULL) {
            free(header->value);
            header->value = NULL;
        }
    }

    if (!uv_is_closing((uv_handle_t *) req->handle)) {
        uv_close((uv_handle_t *) req->handle, on_close);
    }

    return;
}

/**
* Closes current tcp socket after write.
*/
void on_get_write(uv_write_t *req, int status) {
    int i = 0;
    http_header_t *header = NULL;
    http_request_t *http_request = req->data;
    UV_CHECK(status, "on_get_write");

    if (http_request->url != NULL) {
        free(http_request->url);
        http_request->url = NULL;
    }

    if (http_request->method != NULL) {
        free(http_request->method);
        http_request->method = NULL;
    }

    for (i = 0; i < http_request->header_lines; ++i) {
        header = &http_request->headers[i];
        if (header->field != NULL) {
            free(header->field);
            header->field = NULL;
        }
        if (header->value != NULL) {
            free(header->value);
            header->value = NULL;
        }
    }

    if (!uv_is_closing((uv_handle_t *) req->handle)) {
        uv_close((uv_handle_t *) req->handle, on_close);
    }

    return;
}

void on_html_write(uv_write_t *write, int status) {
    char *buf = NULL;
    int i = 0;
    http_header_t *header = NULL;
    http_request_t *http_request = write->data;
    buf = http_request->resp_buf[1].base;

    UV_CHECK(status, "on_html_write");

    if (NULL != buf) {
        free(buf);
        buf = NULL;
    }

    if (http_request->url != NULL) {
        free(http_request->url);
        http_request->url = NULL;
    }

    if (http_request->method != NULL) {
        free(http_request->method);
        http_request->method = NULL;
    }

    for (i = 0; i < http_request->header_lines; ++i) {
        header = &http_request->headers[i];
        if (header->field != NULL) {
            free(header->field);
            header->field = NULL;
        }
        if (header->value != NULL) {
            free(header->value);
            header->value = NULL;
        }
    }

    if (!uv_is_closing((uv_handle_t *) write->handle)) {
        uv_close((uv_handle_t *) write->handle, on_close);
    }

    return;
}

int on_message_complete(http_parser *parser) {
    int i = 0;
    http_header_t *header = NULL;

    printf("***MESSAGE COMPLETE***");

    http_request_t *http_request = parser->data;

    /* now print the ordered http http_request to console */
    printf("url: %s\n", http_request->url);
    printf("method: %s\n", http_request->method);
    for (i = 0; i < MAX_HTTP_HEADERS; ++i) {
        header = &http_request->headers[i];
        if (header->field) {
            printf("Header: %s: %s\n", header->field, header->value);
        }
    }
    printf("body: %s\n", http_request->body);
    printf("\n");

    if (0 == strcmp(http_request->url, "/")) {
        printf("root");
        char *file_contents;
        long input_file_size;

        // send http response header
        http_request->resp_buf[0].base = HTTP_HEADER;
        http_request->resp_buf[0].len = sizeof(HTTP_HEADER) - 1;

        // send http response body
        FILE *input_file = fopen(INDEX_HTML, "rb");
        fseek(input_file, 0, SEEK_END);
        input_file_size = ftell(input_file);
        rewind(input_file);
        file_contents = malloc(input_file_size * (sizeof(char)));
        fread(file_contents, sizeof(char), (size_t) input_file_size, input_file);
        fclose(input_file);

        printf("input_file_size: %ld", input_file_size);

        http_request->resp_buf[1].base = file_contents;
        http_request->resp_buf[1].len = (size_t) input_file_size;

        /* lets send our short http hello world response and close the socket */
        uv_write(&http_request->write, &http_request->client, http_request->resp_buf, 2, on_html_write);
    } else if (0 == strcmp(http_request->url, "/favicon.ico")) {
        printf("favicon");
        http_request->resp_buf[0].base = HTTP_HEADER;
        http_request->resp_buf[0].len = sizeof(HTTP_HEADER) - 1;
        /* lets send our short http hello world response and close the socket */
        uv_write(&http_request->write, &http_request->client, http_request->resp_buf, 1, on_get_write);
    } else {
        printf("undefined url: %s", http_request->url);
        http_request->resp_buf[0].base = HTTP_HEADER;
        http_request->resp_buf[0].len = sizeof(HTTP_HEADER) - 1;
        /* lets send our short http hello world response and close the socket */
        uv_write(&http_request->write, &http_request->client, http_request->resp_buf, 1, on_get_write);
    }

    return 0;
}

void on_connect(uv_stream_t *server_handle, int status) {
    int ret = 0;
    int i = 0;
    UV_CHECK(status, "connect");
    assert((uv_tcp_t *) server_handle == &server);

    /* initialize a new http http_request struct */
    http_request_t *http_request = malloc(sizeof(http_request_t));

    /* create an extra tcp handle for the http_request */
    uv_tcp_init(uv_loop, (uv_tcp_t *) &http_request->client);

    /* set references so we can use our http_request in http_parser and libuv */
    http_request->client.data = http_request;
    http_request->parser.data = http_request;
    http_request->write.data = http_request;

    /* accept the created http_request */
    ret = uv_accept(server_handle, &http_request->client);
    if (0 == ret) {
        http_request->url = NULL;
        http_request->method = NULL;
        http_request->body = NULL;
        http_request->header_lines = 0;
        for (i = 0; i < MAX_HTTP_HEADERS; ++i) {
            http_request->headers[i].field = NULL;
            http_request->headers[i].field_length = 0;
            http_request->headers[i].value = NULL;
            http_request->headers[i].value_length = 0;
        }
        /* initialize our http parser */
        http_parser_init(&http_request->parser, HTTP_REQUEST);
        /* start reading from the tcp http_request socket */
        uv_read_start(&http_request->client, alloc_cb, on_read);
    } else {
        /* we seem to have an error and quit */
        uv_close((uv_handle_t *) &http_request->client, on_close);
        //UV_CHECK(ret, "accept");
    }

    return;
}

int start_server(char *host, int port, http_cb on_message_complete_callback) {
    long cores = 0;
    char cores_string[10] = {0};
    int ret = 0;
    struct sockaddr_in address;

    signal(SIGPIPE, SIG_IGN);

    cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of available CPU cores %ld", cores);
    snprintf(cores_string, sizeof(cores_string), "%ld", cores);
    setenv("UV_THREADPOOL_SIZE", cores_string, 1);

    parser_settings.on_message_begin = on_message_begin;
    parser_settings.on_url = on_url;
    parser_settings.on_header_field = on_header_field;
    parser_settings.on_header_value = on_header_value;
    parser_settings.on_headers_complete = on_headers_complete;
    parser_settings.on_body = on_body;
    parser_settings.on_message_complete = on_message_complete_callback;

    uv_loop = uv_default_loop();

    ret = uv_tcp_init(uv_loop, &server);
    UV_CHECK(ret, "tcp_init");

    //ret = uv_tcp_keepalive(&server, 1, 60);
    //UV_CHECK(ret, "tcp_keepalive");

    ret = uv_ip4_addr(host, port, &address);
    UV_CHECK(ret, "ip4_addr");

    ret = uv_tcp_bind(&server, (const struct sockaddr *) &address, 0);
    UV_CHECK(ret, "tcp_bind");

    ret = uv_listen((uv_stream_t *) &server, MAX_WRITE_HANDLES, on_connect);
    UV_CHECK(ret, "uv_listen");

    printf("Listening on port %d", HTTP_PORT);

    uv_run(uv_loop, UV_RUN_DEFAULT);

    return 0;
}


void uv_boot_write(http_parser *parser, char *data, int32_t data_len) {
    http_request_t *request = parser->data;
    uv_buf_t buf;
    buf.base = data;
    buf.len = data_len;
    uv_write(&request->write, &request->client, &buf, 1, NULL);
}

void uv_boot_end(http_parser *parser, char *data, int data_len) {
    http_request_t *request = parser->data;
    uv_buf_t buf;
    buf.base = data;
    buf.len = data_len;
    uv_write(&request->write, &request->client, &buf, 1, on_html_write);
}
