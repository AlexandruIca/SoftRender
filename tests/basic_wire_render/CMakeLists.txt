add_executable(basic_wire_render ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set_cxx_standard(basic_wire_render 17)
add_coverage(basic_wire_render)
add_sanitizers(basic_wire_render)
target_link_libraries(basic_wire_render PRIVATE ${CMAKE_PROJECT_NAME})
add_test(basic_wire_render basic_wire_render)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/media/african_head.obj
     DESTINATION ${CMAKE_BINARY_DIR}/tests/basic_wire_render/)
