option(SOFTRENDER_COVERAGE "Show code coverage(mostly for CI)" OFF)

function(add_coverage COV_TARGET)
  if(${SOFTRENDER_COVERAGE} AND "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_compile_options(${COV_TARGET} PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_libraries(${COV_TARGET} PRIVATE -fprofile-arcs -ftest-coverage)
  endif()
endfunction()
