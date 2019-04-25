//
// Created by yunp on 2019-04-25.
//

#include <stdio.h>
#include <uv_boot.h>
#include <stdlib.h>


int message_complete_callback(http_parser *parser) {

    char *respContent = "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/html\r\n" \
    "\r\n" \
    "Hello World";

    http_request_t *request = parser->data;
    uv_buf_t buf;
    buf.base = respContent;
    buf.len = strlen(buf.base);
    uv_write(&request->write, &request->stream, &buf, 1, on_html_write);
    return 0;
}


int main() {
    printf("Server started at port 9000\n");

    start_server("0.0.0.0", 9000, message_complete_callback);
}