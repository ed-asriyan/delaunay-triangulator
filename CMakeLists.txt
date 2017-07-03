cmake_minimum_required(VERSION 3.5)
project(delaunay_triangulator)

set(CMAKE_C_STANDARD 11)

find_package(OpenCV REQUIRED)

add_subdirectory(delaunay_transformations)

set(SOURCE_FILES
        main.c
        )
add_executable(delaunay_triangulator ${SOURCE_FILES})
target_link_libraries(delaunay_triangulator
        delaunay_transformations
        ${OpenCV_LIBS}
        )
