
file(GLOB VW_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/vw/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB VW_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(VW_UI_H ${VW_UI})
#qt5_add_resources(VW_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(vw SHARED
            ${VW_SRC} 
            ${VW_MOC_SRC}
#            ${VW_UI_H} 
#            ${VW_QRC}
           )

target_compile_definitions(vw
    PRIVATE
        VW_LIBRARY
    )

target_include_directories(vw 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vw
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(vw 
#    PRIVATE
#
#    )

#target_link_libraries(vw 
#    PRIVATE
#        
#    )

qt5_use_modules(vw 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(vw
#        ${VW_SRC} 
#        ${VW_UI}
#    )

