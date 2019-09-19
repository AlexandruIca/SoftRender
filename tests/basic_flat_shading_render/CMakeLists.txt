add_executable(basic_flat_shading_render
               ${CMAKE_CURRENT_SOURCE_DIR}/basic_flat_shading_render.cpp)
set_cxx_standard(basic_flat_shading_render 17)
add_coverage(basic_flat_shading_render)
add_sanitizers(basic_flat_shading_render)
target_link_libraries(basic_flat_shading_render PRIVATE ${CMAKE_PROJECT_NAME})
add_test(basic_flat_shading_render basic_flat_shading_render)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/media/african_head.obj
     DESTINATION ${CMAKE_BINARY_DIR}/tests/basic_flat_shading_render/)
