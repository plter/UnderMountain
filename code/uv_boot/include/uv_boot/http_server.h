//
// Created by yunp on 2019-04-25.
//

#ifndef UV_BOOT_HTTP_SERVER_H
#define UV_BOOT_HTTP_SERVER_H

#include "http_parser.h"
#include <uv.h>

#define MAX_HTTP_HEADERS (20)

/**
* Represents a single http header.
*/
typedef struct {
    char *field;
    char *value;
    size_t field_length;
    size_t value_length;
} http_header_t;

/**
* Represents a http request with internal dependencies.
*
* - write request for sending the response
* - reference to tcp socket as write stream
* - instance of http_parser parser
* - string of the http url
* - string of the http method
* - amount of total header lines
* - http header array
* - body content
*/
typedef struct {
    uv_write_t write;
    uv_stream_t client;
    http_parser parser;
    char *url;
    char *method;
    int header_lines;
    http_header_t headers[MAX_HTTP_HEADERS];
    char *body;
    size_t body_length;
    uv_buf_t resp_buf[2];
} http_request_t;

void on_close(uv_handle_t *handle);

void on_html_write(uv_write_t *write, int status);

int start_server(char *host, int port, http_cb on_message_complete_callback);

void uv_boot_write(http_parser *parser, char *data, int data_len);

void uv_boot_end(http_parser *parser, char *data, int data_len);

#endif //UV_BOOT_HTTP_SERVER_H
