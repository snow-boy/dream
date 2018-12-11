set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB QTWIDGETS_EXT_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtwidgets_ext/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB QTWIDGETS_EXT_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(QTWIDGETS_EXT_UI_H ${QTWIDGETS_EXT_UI})
#qt5_add_resources(QTWIDGETS_EXT_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(qtwidgets_ext STATIC
            ${QTWIDGETS_EXT_SRC} 
            ${QTWIDGETS_EXT_MOC_SRC}
#            ${QTWIDGETS_EXT_UI_H} 
#            ${QTWIDGETS_EXT_QRC}
           )

#target_compile_definitions(qtwidgets_ext  
#    PRIVATE 
#        
#    )

target_include_directories(qtwidgets_ext 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/qtwidgets_ext
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(qtwidgets_ext 
#    PRIVATE
#
#    )

#target_link_libraries(qtwidgets_ext 
#    PRIVATE
#        
#    )

qt5_use_modules(qtwidgets_ext 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(qtwidgets_ext
#        ${QTWIDGETS_EXT_SRC} 
#        ${QTWIDGETS_EXT_UI}
#    )

