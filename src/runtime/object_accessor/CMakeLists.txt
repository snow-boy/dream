include(matrix_qt)

file(GLOB OBJECT_ACCESSOR_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/object_accessor/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB OBJECT_ACCESSOR_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(OBJECT_ACCESSOR_UI_H ${OBJECT_ACCESSOR_UI})
#qt5_add_resources(OBJECT_ACCESSOR_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_matrix_shared_library(object_accessor
                    ${OBJECT_ACCESSOR_SRC} 
#                    ${OBJECT_ACCESSOR_UI_H} 
#                    ${OBJECT_ACCESSOR_QRC}
                )

target_compile_definitions(object_accessor
    PRIVATE
        OBJECT_ACCESSOR_LIBRARY
    )

target_include_directories(object_accessor 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/object_accessor
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_matrix_modules(object_accessor 
#    PRIVATE
#
#    )

#target_link_libraries(object_accessor 
#    PRIVATE
#        
#    )

target_link_qt_modules(object_accessor
    PRIVATE
        Core
#        Widgets
    )

#target_generate_qt_translation(object_accessor
#        ${OBJECT_ACCESSOR_SRC} 
#        ${OBJECT_ACCESSOR_UI}
#    )

#add_subdirectory(test)
