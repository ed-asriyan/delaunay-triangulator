cmake_minimum_required(VERSION 3.5)
project(delaunay_triangulator)

set(CMAKE_C_STANDARD 11)

# loading git dependecies
message("Downloading dependencies...")
execute_process(COMMAND git submodule update --init)
message("Done.")

find_package(OpenCV REQUIRED)

add_subdirectory(delaunay_transformations)
add_subdirectory(argparse)

set(SOURCE_FILES
        main.c
        )
add_executable(delaunay_triangulator ${SOURCE_FILES})
target_link_libraries(delaunay_triangulator
        delaunay_transformations
        argparse
        ${OpenCV_LIBS}
        )
