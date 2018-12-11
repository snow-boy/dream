set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${bin_dir})

add_subdirectory(cradle)
add_subdirectory(vw)
add_subdirectory(life)
add_subdirectory(qtwidgets_ext)
add_subdirectory(ui_vw_editor)
add_subdirectory(eigen_qt)
