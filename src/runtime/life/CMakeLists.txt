set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB LIFE_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/life/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB LIFE_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(LIFE_UI_H ${LIFE_UI})
#qt5_add_resources(LIFE_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(life SHARED
            ${LIFE_SRC} 
            ${LIFE_MOC_SRC}
#            ${LIFE_UI_H} 
#            ${LIFE_QRC}
           )

target_compile_definitions(life
    PRIVATE
        LIFE_LIBRARY
    )

target_include_directories(life 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/life
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(life 
#    PRIVATE
#
#    )

target_link_libraries(life
    PUBLIC
        vw
    )

qt5_use_modules(life 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(life
#        ${LIFE_SRC} 
#        ${LIFE_UI}
#    )

