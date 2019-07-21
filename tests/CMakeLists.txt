enable_testing()

function( build_test TEST_NAME TEST_FILE )
    add_executable( ${TEST_NAME} ${TEST_FILE} )
    set_cxx_standard( ${TEST_NAME} 17 )
    target_link_libraries( ${TEST_NAME} PRIVATE ${CMAKE_PROJECT_NAME} )
    add_test( ${TEST_NAME} ${TEST_NAME} )
    set_tests_properties( ${TEST_NAME} PROPERTIES TIMEOUT 2 )
endfunction()

build_test( setup ${CMAKE_CURRENT_SOURCE_DIR}/setup.cpp )

