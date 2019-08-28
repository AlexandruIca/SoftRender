cmake_minimum_required( VERSION 3.10 )

# MacOS bug with spaces in library path
if( APPLE AND POLICY CMP0004 )
    cmake_policy( SET CMP0004 OLD )
endif()

project( softrender LANGUAGES CXX )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )
include( SetCXXStandard )
include( Sanitizers )

find_package( SDL2 CONFIG REQUIRED )
find_path( SDL2_INCLUDE_DIRS NAMES SDL2/SDL.h )

message( "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}" )

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src/ )

option( SOFTRENDER_MOCKING "Mock creating a window" OFF )

add_library( ${CMAKE_PROJECT_NAME} STATIC ${SOFTRENDER_SRC_FILES} )
target_include_directories( ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${SOFTRENDER_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)
set_cxx_standard( ${CMAKE_PROJECT_NAME} 17 )
target_compile_definitions( ${CMAKE_PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:SOFTRENDER_DEBUG>
    $<$<CONFIG:Release>:SOFTRENDER_RELEASE>
    $<$<BOOL:${SOFTRENDER_MOCKING}>:SOFTRENDER_MOCKING>
)
target_compile_options( ${CMAKE_PROJECT_NAME}
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
            -Wall -Wextra -Wpedantic >
    $<$<CXX_COMPILER_ID:GNU>:
            -Wall -pedantic -pedantic-errors >
    $<$<CXX_COMPILER_ID:MSVC>:
            /W4 /permissive- /analyze >
)
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    SDL2::SDL2main
    SDL2::SDL2-static
)

option(
    SOFTRENDER_BUILD_TESTS
    "Build all the tests that come with the library"
    OFF
)

if( ${SOFTRENDER_BUILD_TESTS} )
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests/ )
endif()

option(
    SOFTRENDER_BUILD_DOCS
    "Build the documentation that comes with the library"
    OFF
)

if( ${SOFTRENDER_BUILD_DOCS} )
    find_package( Doxygen )

    if( DOXYGEN_FOUND )
        add_custom_target( documentation ALL
            COMMAND ${CMAKE_COMMAND} -E echo "Building documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
    else()
        message( "You need doxygen to build the documentation!" )
    endif()
endif()

option(
    SOFTRENDER_BUILD_DOCS_MCSS
    "Build better looking documentation with doxygen-mcss"
    OFF
)

if( ${SOFTRENDER_BUILD_DOCS_MCSS} )
    add_custom_target( documentation_mcss ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Building documentation with doxygen-mcss..."
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../m.css/documentation/doxygen.py ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-mcss
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif()
