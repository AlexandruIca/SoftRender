enable_testing()

function(build_test TEST_NAME TEST_FILE)
  add_executable(${TEST_NAME} ${TEST_FILE})
  set_cxx_standard(${TEST_NAME} 17)
  add_coverage(${TEST_NAME})
  add_sanitizers(${TEST_NAME})
  target_compile_definitions(${TEST_NAME} PUBLIC
                             $<$<CONFIG:Debug>:SOFTRENDER_DEBUG>)
  target_include_directories(${TEST_NAME}
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers/)
  target_link_libraries(${TEST_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

build_test(setup ${CMAKE_CURRENT_SOURCE_DIR}/setup.cpp)
build_test(black_screen ${CMAKE_CURRENT_SOURCE_DIR}/black_screen.cpp)
build_test(point ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp)
build_test(point_coord2D ${CMAKE_CURRENT_SOURCE_DIR}/point_coord2D.cpp)
build_test(canvas_manipulation
           ${CMAKE_CURRENT_SOURCE_DIR}/canvas_manipulation.cpp)
build_test(line ${CMAKE_CURRENT_SOURCE_DIR}/line.cpp)
build_test(colors ${CMAKE_CURRENT_SOURCE_DIR}/colors.cpp)
build_test(vec ${CMAKE_CURRENT_SOURCE_DIR}/vec.cpp)
build_test(triangle ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  build_test(exception ${CMAKE_CURRENT_SOURCE_DIR}/exception.cpp)
endif()

add_subdirectory(basic_wire_render/)
add_subdirectory(basic_flat_shading_render/)
