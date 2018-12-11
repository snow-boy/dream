set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_dir})

file(GLOB EVENTS_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/events/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

#file(GLOB EVENTS_UI
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
#)

#qt5_wrap_ui(EVENTS_UI_H ${EVENTS_UI})
#qt5_add_resources(EVENTS_QRC ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.qrc)

add_library(events STATIC
            ${EVENTS_SRC} 
            ${EVENTS_MOC_SRC}
#            ${EVENTS_UI_H} 
#            ${EVENTS_QRC}
           )

#target_compile_definitions(events  
#    PRIVATE 
#        
#    )

target_include_directories(events 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/events
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

#target_include_modules(events 
#    PRIVATE
#
#    )

#target_link_libraries(events 
#    PRIVATE
#        
#    )

qt5_use_modules(events 
    LINK_PRIVATE
        Core
    )

#target_generate_qt_translation(events
#        ${EVENTS_SRC} 
#        ${EVENTS_UI}
#    )

