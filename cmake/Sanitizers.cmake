option( USE_ADDRESS_SANITIZER "Build with -fsanitize=address" OFF )
option( USE_LEAK_SANITIZER "Build with -fsanitize=leak" OFF )
option( USE_UNDEFINED_SANITIZER "Build with -fsanitize=undefined" OFF )
option( USE_THREAD_SANITIZER "Build with -fsanitize=thread" OFF )

function( add_sanitizers SANITIZER_TARGET )
    set( SANITIZERS "" )

    if( ${USE_ADDRESS_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}address," )
    endif()

    if( ${USE_LEAK_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}leak," )
    endif()

    if( ${USE_UNDEFINED_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}undefined," )
    endif()

    if( ${USE_THREAD_SANITIZER} )
        set( SANITIZERS "${SANITIZERS}thread," )
    endif()

    if( ${USE_ADDRESS_SANITIZER}
            OR
        ${USE_LEAK_SANITIZER}
            OR
        ${USE_UNDEFINED_SANITIZER}
            OR
        ${USE_THREAD_SANITIZER}
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
