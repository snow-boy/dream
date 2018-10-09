set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})
message(--------------------------- ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp
    )

add_executable(dream ${SRC})

target_link_libraries(dream
    PRIVATE
        cradle
    )

qt5_use_modules(dream
    LINK_PRIVATE
        Core
        Widgets
    )
