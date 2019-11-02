option(NOT_USING_TRAVIS "Travis doesn't like -Werror" ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SOFTRENDER_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/softrender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wavefront_reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mouse_button.cpp)

set(SOFTRENDER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(SOFTRENDER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/softrender.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/vec.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/wavefront_reader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/keys.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mouse_button.hpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOFTRENDER_SRC_FILES})
add_library(${CMAKE_PROJECT_NAME}-shared SHARED ${SOFTRENDER_SRC_FILES})
target_include_directories(
  ${CMAKE_PROJECT_NAME} PUBLIC ${SOFTRENDER_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})
target_include_directories(
  ${CMAKE_PROJECT_NAME}-shared PUBLIC ${SOFTRENDER_INCLUDE_DIRS}
                                      ${SDL2_INCLUDE_DIRS})
set_cxx_standard(${CMAKE_PROJECT_NAME} 17)
set_cxx_standard(${CMAKE_PROJECT_NAME}-shared 17)
target_compile_definitions(
  ${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:SOFTRENDER_DEBUG>
  $<$<CONFIG:Release>:SOFTRENDER_RELEASE>
  $<$<BOOL:${SOFTRENDER_MOCKING}>:SOFTRENDER_MOCKING>)
target_compile_options(
  ${CMAKE_PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
    -Wall
    $<$<BOOL:${NOT_USING_TRAVIS}>:-Werror>
    -Wextra
    -Wpedantic
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Release>:-O3>
    >
    $<$<CXX_COMPILER_ID:GNU>:
    -Wall
    -Werror
    -pedantic
    -pedantic-errors
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Release>:-O3>
    >
    $<$<CXX_COMPILER_ID:MSVC>:
    /W4
    /WX
    /permissive-
    /analyze
    >)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME}-shared PRIVATE ${SDL2_LIBRARIES})

add_coverage(${CMAKE_PROJECT_NAME})
add_sanitizers(${CMAKE_PROJECT_NAME})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(TARGETS ${CMAKE_PROJECT_NAME}-shared DESTINATION lib)
install(FILES ${SOFTRENDER_HEADERS} DESTINATION include)

set(CPACK_DEBIAN_PACKAGE_MANTAINER "Alexandru Ica Gabriel")

include(CPack)
