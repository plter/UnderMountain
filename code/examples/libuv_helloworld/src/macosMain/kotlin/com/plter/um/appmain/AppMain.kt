package com.plter.um.appmain

import com.plter.um.uv.*
import kotlinx.cinterop.CValuesRef
import kotlinx.cinterop.sizeOf
import platform.posix.free
import platform.posix.malloc
import platform.posix.printf


fun main() {
    val loop = malloc(sizeOf<uv_loop_t>().toULong()) as CValuesRef<uv_loop_t>
    uv_loop_init(loop)

    printf("Now quitting.\n")
    uv_run(loop, UV_RUN_DEFAULT)

    uv_loop_close(loop);
    free(loop)
}