set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_dir}/modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_dir}/modules)

add_subdirectory(main_ui)
add_subdirectory(modeling)
add_subdirectory(life)
