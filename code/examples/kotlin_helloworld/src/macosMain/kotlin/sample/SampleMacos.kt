package sample

import kotlinx.cinterop.cstr
import platform.posix.printf

fun hello(): String = "你好, Kotlin/Native!"

fun main() {
    println(hello())

    val text = "中文"
    printf("%s\n", text.cstr)
}
