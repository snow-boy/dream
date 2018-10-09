cmake_minimum_required(VERSION 3.8.0)

set(prj_name dream)
set(bin_dir ${CMAKE_BINARY_DIR}/bin)

project(${prj_name})

# begin qt
list(APPEND CMAKE_MODULE_PATH "$ENV{QT_PATH}/Qt5.4.0/x64/5.4/msvc2013_64_opengl/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "$ENV{QT_PATH}/Qt5.4.0/x64/5.4/msvc2013_64_opengl/lib/cmake")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# end qt

function(target_include_modules name)
    list(REMOVE_AT ARGV 0)
    set(includes "")
    foreach (module ${ARGV})
        string(TOUPPER ${module} temp)
        if(${temp} STREQUAL "PRIVATE" OR ${temp} STREQUAL "PUBLIC" OR ${temp} STREQUAL "INTERFACE")
            list(APPEND includes ${temp})
            continue()
        endif(${temp} STREQUAL "PRIVATE" OR ${temp} STREQUAL "PUBLIC" OR ${temp} STREQUAL "INTERFACE")
        list(APPEND includes ${CMAKE_SOURCE_DIR}/src/modules/${module}/include)
    endforeach(module ${ARGV})
    target_include_directories(${name} ${includes})
endfunction(target_include_matrix_modules)

function(target_generate_qt_translation name)
    set(src_files)
    list(REMOVE_AT ARGV 0)
    foreach (src ${ARGV})
        list(APPEND src_files ${src})
    endforeach(src ${ARGV})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/lang)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/lang)
    endif(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/lang)
    add_custom_command(TARGET ${name} POST_BUILD
                COMMAND ${Qt5_LUPDATE_EXECUTABLE}
                ARGS ${src_files} -ts ${CMAKE_CURRENT_SOURCE_DIR}/src/lang/lang.ts
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endfunction(target_generate_qt_translation)

add_subdirectory(src)

