cmake_minimum_required(VERSION 3.5)
project(delaunay_transformations)

set(CMAKE_C_STANDARD 11)

# loading git module with delaunay implementation
find_path(DEPENDENCY_DELAUANAY_PATH delaunay)
if (NOT EXISTS ${DEPENDENCY_DELAUANAY_PATH})
    message("Downloading dependencies...")
    execute_process(COMMAND git submodule update --init)
    message("Done.")
endif ()

set(DELAUNAY_FILES
        delaunay/delaunay.h delaunay/delaunay.c)
add_library(delaunay ${DELAUNAY_FILES})


set(SOURCE_FILES
        dt.c dt.h)
add_library(delaunay_transformations ${SOURCE_FILES})
target_link_libraries(delaunay_transformations delaunay)
