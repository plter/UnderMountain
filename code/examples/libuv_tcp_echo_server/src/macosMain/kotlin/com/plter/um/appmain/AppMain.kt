package com.plter.um.appmain

import com.plter.um.uv.*
import kotlinx.cinterop.*
import platform.posix.*


fun main() {

    memScoped {
        val loop = uv_default_loop()
        val server = alloc<uv_tcp_t>()
        uv_tcp_init(loop, server.ptr)

        val addr = alloc<sockaddr_in>()
        uv_ip4_addr("0.0.0.0", 9000, addr.ptr)
        uv_tcp_bind(server.ptr, addr.ptr as CValuesRef<sockaddr>, 0)
        val r = uv_listen(server.ptr as CValuesRef<uv_stream_t>, 128, staticCFunction { server, status ->
            if (status < 0) {
                fprintf(stderr, "New connection error %d\n", status)
                return@staticCFunction
            }
            println("New connection")
        })
        if (r != 0) {
            fprintf(stderr, "Listen error %d\n", r)
        }
        uv_run(loop, UV_RUN_DEFAULT)
    }
}