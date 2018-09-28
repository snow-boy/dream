cmake_minimum_required(VERSION 3.8.0)

set(prj_name dream)
set(bin_dir ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

project(${prj_name})

add_subdirectory(src)

