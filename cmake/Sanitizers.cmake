option( SOFTRENDER_USE_ADDRESS_SANITIZER "Build with -fsanitize=address" OFF )
option( SOFTRENDER_USE_LEAK_SANITIZER "Build with -fsanitize=leak" OFF )
option( SOFTRENDER_USE_UNDEFINED_SANITIZER "Build with -fsanitize=undefined" OFF )
option( SOFTRENDER_USE_THREAD_SANITIZER "Build with -fsanitize=thread" OFF )

function( add_sanitizers SANITIZER_TARGET )
    set( SANITIZERS "" )

    if( ${SOFTRENDER_USE_ADDRESS_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}address," )
    endif()

    if( ${SOFTRENDER_USE_LEAK_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}leak," )
    endif()

    if( ${SOFTRENDER_USE_UNDEFINED_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}undefined," )
    endif()

    if( ${SOFTRENDER_USE_THREAD_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}thread," )
    endif()

    if( ${SOFTRENDER_USE_ADDRESS_SANITIZER}
            OR
            ${SOFTRENDER_USE_LEAK_SANITIZER}
            OR
            ${SOFTRENDER_USE_UNDEFINED_SANITIZER}
            OR
            ${SOFTRENDER_USE_THREAD_SANITIZER}
    )
        target_compile_options(
            ${SANITIZER_TARGET}
            PRIVATE
            -fno-omit-frame-pointer
            -fsanitize=${SANITIZERS}
        )
        target_link_libraries(
            ${SANITIZER_TARGET}
            PRIVATE
            -fsanitize=${SANITIZERS}
        )
    endif()
endfunction()
