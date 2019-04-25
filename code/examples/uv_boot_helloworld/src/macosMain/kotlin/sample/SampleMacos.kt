package sample

import com.plter.um.uv_boot.start_server
import kotlinx.cinterop.cstr
import kotlinx.cinterop.staticCFunction

fun hello(): String = "Hello, Kotlin/Native!"

fun main() {
    start_server("0.0.0.0".cstr, 9000, staticCFunction { req ->
        return@staticCFunction 0
    })
}