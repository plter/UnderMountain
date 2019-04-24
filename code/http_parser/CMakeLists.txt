cmake_minimum_required(VERSION 3.14)
project(http_parser C)

set(CMAKE_C_STANDARD 11)

add_library(http_parser STATIC http_parser.c)