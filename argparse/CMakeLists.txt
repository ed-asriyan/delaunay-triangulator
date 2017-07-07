cmake_minimum_required(VERSION 3.5)
project(argparse)

set(CMAKE_C_STANDARD 11)

set(ARGPARSE_FILES
        argparse/argparse.h argparse/argparse.c
        )
add_library(argparse ${ARGPARSE_FILES})
target_link_libraries(argparse m)
