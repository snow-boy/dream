
file(GLOB MODELING_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/modeling/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB MODELING_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
)

qt5_wrap_ui(MODELING_UI_H ${MODELING_UI})
#qt5_add_resources(MODELING_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(modeling SHARED
            ${MODELING_SRC} 
            ${MODELING_UI_H}
#            ${MODELING_QRC}
           )

#target_compile_definitions(modeling  
#    PRIVATE 
#        
#    )

target_include_directories(modeling 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/modeling
    )

target_include_modules(modeling
    PRIVATE
        main_ui
    )

target_link_libraries(modeling
    PRIVATE
        cradle
        life
        vw
        ui_vw_editor
        qtwidgets_ext
    )

qt5_use_modules(modeling 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(modeling
#        ${MODELING_SRC} 
#        ${MODELING_UI}
#    )

