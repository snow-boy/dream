set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB EIGEN_QT_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/eigen_qt/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB EIGEN_QT_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(EIGEN_QT_UI_H ${EIGEN_QT_UI})
#qt5_add_resources(EIGEN_QT_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(eigen_qt STATIC
            ${EIGEN_QT_SRC} 
#            ${EIGEN_QT_UI_H} 
#            ${EIGEN_QT_QRC}
           )

#target_compile_definitions(eigen_qt  
#    PRIVATE 
#        
#    )

target_include_directories(eigen_qt 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/eigen_qt
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(eigen_qt 
#    PRIVATE
#
#    )

target_link_libraries(eigen_qt
    PUBLIC
        eigen
    )

qt5_use_modules(eigen_qt 
    LINK_PRIVATE
        Core
        Widgets
    )

#target_generate_qt_translation(eigen_qt
#        ${EIGEN_QT_SRC} 
#        ${EIGEN_QT_UI}
#    )

