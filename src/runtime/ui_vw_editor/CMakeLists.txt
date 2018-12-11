set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB UI_VW_EDITOR_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui_vw_editor/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB UI_VW_EDITOR_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
)

qt5_wrap_ui(UI_VW_EDITOR_UI_H ${UI_VW_EDITOR_UI})
#qt5_add_resources(UI_VW_EDITOR_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(ui_vw_editor STATIC
            ${UI_VW_EDITOR_SRC} 
            ${UI_VW_EDITOR_MOC_SRC}
            ${UI_VW_EDITOR_UI_H}
#            ${UI_VW_EDITOR_QRC}
           )

#target_compile_definitions(ui_vw_editor  
#    PRIVATE 
#        
#    )

target_include_directories(ui_vw_editor 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ui_vw_editor
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(ui_vw_editor 
#    PRIVATE
#
#    )

target_link_libraries(ui_vw_editor
    PUBLIC
        qtwidgets_ext
        vw
        eigen
        eigen_qt
    )

qt5_use_modules(ui_vw_editor 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(ui_vw_editor
#        ${UI_VW_EDITOR_SRC} 
#        ${UI_VW_EDITOR_UI}
#    )

