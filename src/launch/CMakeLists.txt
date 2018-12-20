set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_dir})

file(GLOB SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp
    )

add_executable(dream ${SRC})

target_link_libraries(dream
    PRIVATE
        cradle
        vw
    )

qt5_use_modules(dream
    LINK_PRIVATE
        Core
        Widgets
    )
