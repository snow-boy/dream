set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB CRADLE_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cradle/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

qt5_wrap_cpp(CRADLE_MOC_SRC ${CRADLE_SRC})

add_library(cradle SHARED ${CRADLE_SRC} ${CRADLE_MOC_SRC})

qt5_use_modules(cradle
    LINK_PRIVATE
        Core
    )

target_include_directories(cradle 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cradle
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_compile_definitions(cradle 
    PRIVATE
        CRADLE_LIBRARY
    )
 
