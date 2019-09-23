add_executable(simple_snake ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set_cxx_standard(simple_snake 17)
target_link_libraries(simple_snake
                      PRIVATE $<$<BOOL:WIN32>:${CMAKE_PROJECT_NAME}>
                              $<$<BOOL:UNIX>:${CMAKE_PROJECT_NAME}-shared>
                              $<$<BOOL:APPLE>:${CMAKE_PROJECT_NAME}-shared>)
