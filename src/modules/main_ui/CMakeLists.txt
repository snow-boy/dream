set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir}/modules)

file(GLOB MAIN_UI_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/main_ui/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB MAIN_UI_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
)

qt5_wrap_ui(MAIN_UI_UI_H ${MAIN_UI_UI})
qt5_add_resources(MAIN_UI_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.qrc)

add_library(main_ui SHARED
            ${MAIN_UI_SRC}
            ${MAIN_UI_UI_H}
            ${MAIN_UI_QRC}
           )

#target_compile_definitions(main_ui  
#    PRIVATE 
#
#    )

target_include_directories(main_ui 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/main_ui
    )

#target_include_modules(main_ui 
#    PRIVATE
#
#    )

target_link_libraries(main_ui
    PRIVATE
        cradle
        vw
    )

qt5_use_modules(main_ui 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(main_ui
#        ${MAIN_UI_SRC} 
#        ${MAIN_UI_UI}
#    )

