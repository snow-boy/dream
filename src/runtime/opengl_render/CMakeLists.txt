set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB OPENGL_RENDER_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_render/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB OPENGL_RENDER_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(OPENGL_RENDER_UI_H ${OPENGL_RENDER_UI})
qt5_add_resources(OPENGL_RENDER_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(opengl_render SHARED
            ${OPENGL_RENDER_SRC}
#            ${OPENGL_RENDER_UI_H} 
            ${OPENGL_RENDER_QRC}
           )

target_compile_definitions(opengl_render
    PRIVATE
        OPENGL_RENDER_LIBRARY
    )

target_include_directories(opengl_render 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_render
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(opengl_render 
#    PRIVATE
#
#    )

target_link_libraries(opengl_render
    PRIVATE
        vw
    )

qt5_use_modules(opengl_render 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(opengl_render
#        ${OPENGL_RENDER_SRC} 
#        ${OPENGL_RENDER_UI}
#    )

