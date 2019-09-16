set(SOFTRENDER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/softrender.cpp)

set(SOFTRENDER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOFTRENDER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/softrender.hpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/include/vec.hpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOFTRENDER_SRC_FILES})
add_library(${CMAKE_PROJECT_NAME}-shared SHARED ${SOFTRENDER_SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME}
                           PUBLIC ${SOFTRENDER_INCLUDE_DIRS}
                                  ${SDL2_INCLUDE_DIRS})
target_include_directories(${CMAKE_PROJECT_NAME}-shared
                           PUBLIC ${SOFTRENDER_INCLUDE_DIRS}
                                  ${SDL2_INCLUDE_DIRS})
set_cxx_standard(${CMAKE_PROJECT_NAME} 17)
set_cxx_standard(${CMAKE_PROJECT_NAME}-shared 17)
target_compile_definitions(${CMAKE_PROJECT_NAME}
                           PRIVATE
                           $<$<CONFIG:Debug>:SOFTRENDER_DEBUG>
                           $<$<CONFIG:Release>:SOFTRENDER_RELEASE>
                           $<$<BOOL:${SOFTRENDER_MOCKING}>:SOFTRENDER_MOCKING>)
target_compile_options(
  ${CMAKE_PROJECT_NAME}
  PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
          -Wall
          -Wextra
          -Wpedantic
          >
          $<$<CXX_COMPILER_ID:GNU>:
          -Wall
          -pedantic
          -pedantic-errors
          >
          $<$<CXX_COMPILER_ID:MSVC>:
          /W4
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
