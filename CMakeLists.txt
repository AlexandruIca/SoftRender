cmake_minimum_required(VERSION 3.10)

# MacOS bug with spaces in library path
if(APPLE AND POLICY CMP0004)
  cmake_policy(SET CMP0004 OLD)
endif()

project(SoftRender LANGUAGES CXX VERSION 0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(SetCXXStandard)
include(Sanitizers)
include(CodeCoverage)

option(USE_VCPKG_ON_MACOS "Set this to ON if you have vcpkg installed on MacOS"
       OFF)

if(NOT APPLE OR ${USE_VCPKG_ON_MACOS})
  find_package(SDL2 CONFIG REQUIRED)
  find_path(SDL2_INCLUDE_DIRS NAMES SDL2/SDL.h)
  set(SDL2_LIBRARIES SDL2::SDL2main SDL2::SDL2-static)
else()
  find_package(SDL2 REQUIRED)
endif()

message("SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")

option(SOFTRENDER_MOCKING "Mock creating a window" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/)

option(SOFTRENDER_BUILD_TESTS "Build all the tests that come with the library"
       OFF)

if(${SOFTRENDER_BUILD_TESTS})
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/)
endif()

option(SOFTRENDER_BUILD_DOCS
       "Build the documentation that comes with the library" OFF)

if(${SOFTRENDER_BUILD_DOCS})
  find_package(Doxygen)

  if(DOXYGEN_FOUND)
    add_custom_target(documentation ALL
                      COMMAND ${CMAKE_COMMAND}
                              -E
                              echo
                              "Building documentation..."
                      COMMAND ${DOXYGEN_EXECUTABLE}
                              ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      VERBATIM)
  else()
    message("You need doxygen to build the documentation!")
  endif()
endif()

option(SOFTRENDER_BUILD_DOCS_MCSS
       "Build better looking documentation with doxygen-mcss" OFF)

if(${SOFTRENDER_BUILD_DOCS_MCSS})
  add_custom_target(
    documentation_mcss ALL
    COMMAND ${CMAKE_COMMAND}
            -E
            echo
            "Building documentation with doxygen-mcss..."
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../m.css/documentation/doxygen.py
            ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-mcss
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endif()
