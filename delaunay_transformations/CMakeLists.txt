cmake_minimum_required(VERSION 3.5)
project(delaunay_transformations)

set(CMAKE_C_STANDARD 11)

set(DELAUNAY_FILES
        delaunay/delaunay.h delaunay/delaunay.c
        )
add_library(delaunay ${DELAUNAY_FILES})

find_package(OpenCV REQUIRED)

set(SOURCE_FILES
        triangulator.c triangulator.h
        drawer.c drawer.h
        )
add_library(delaunay_transformations ${SOURCE_FILES})
target_link_libraries(delaunay_transformations
        delaunay
        ${OpenCV_LIBS}
        )
