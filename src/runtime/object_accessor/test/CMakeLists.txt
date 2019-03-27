include(matrix_qt)

file(GLOB SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_matrix_hmcp_application(object_accessor_test ${SRC})

target_link_libraries(object_accessor_test
        object_accessor
    )

target_link_qt_modules(object_accessor_test
        Core
#        Widgets
    )
