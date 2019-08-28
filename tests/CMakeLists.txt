enable_testing()

function( build_test TEST_NAME TEST_FILE )
    add_executable( ${TEST_NAME} ${TEST_FILE} )
    set_cxx_standard( ${TEST_NAME} 17 )
    target_link_libraries( ${TEST_NAME} PRIVATE ${CMAKE_PROJECT_NAME} )
    add_test( ${TEST_NAME} ${TEST_NAME} )
    set_tests_properties( ${TEST_NAME} PROPERTIES TIMEOUT 2 )
endfunction()

build_test( setup ${CMAKE_CURRENT_SOURCE_DIR}/setup.cpp )
build_test( black_screen ${CMAKE_CURRENT_SOURCE_DIR}/black_screen.cpp )
build_test( point ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp )
build_test( point_coord2D ${CMAKE_CURRENT_SOURCE_DIR}/point_coord2D.cpp )
build_test( canvas_manipulation ${CMAKE_CURRENT_SOURCE_DIR}/canvas_manipulation.cpp )

if( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
    build_test( exception ${CMAKE_CURRENT_SOURCE_DIR}/exception.cpp )
endif()
