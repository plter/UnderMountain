package sample

import com.plter.um.uv_boot.start_server
import com.plter.um.uv_boot.uv_boot_end
import kotlinx.cinterop.cstr
import kotlinx.cinterop.staticCFunction

fun hello(): String = "Hello, Kotlin/Native!"

val content = "HTTP/1.1 200 OK\r\n" +
        "Content-Type: text/html\r\n\r\n" +
        "Hello World";

fun main() {
    start_server("0.0.0.0".cstr, 9000, staticCFunction { parser ->
        uv_boot_end(parser, content.cstr, content.length)
        return@staticCFunction 0
    })
}