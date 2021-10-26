cmake_minimum_required(VERSION 3.10.2)

function(set_target_c_standard target standard)
set_target_properties(
    ${target}
    PROPERTIES
        C_STANDARD ${standard}
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
)
endfunction()

function(enable_target_c_warnings target)
    target_compile_options(
        ${target}
        PRIVATE
            -Wall
            -Wextra
            -Werror
            -Wundef
            -Wuninitialized
            -Wshadow
            -Wpointer-arith
            -Wcast-align
            -Wcast-qual
            -Wunused-parameter
            -Wdouble-promotion
            -Wnull-dereference
          
    )
    #GCC Specific flags
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(
        ${target}
        PRIVATE
            -Wlogical-op
            -Wduplicated-cond
            -Wduplicated-branches
    )
    endif()
endfunction()

#enable_target_c_sanitizer(${my_target} "address")
# Available sanitizers
#
# GCC: address, thread, leak, undefined
# CLANG: address, memory, thread, leak, undefined
function(enable_target_c_sanitizer target sanitizer)
    if(NOT CMAKE_BUILD_TYPE OR NOT CMAKE_BUILD_TYPE MATCHES Debug)
        message(
            FATAL_ERROR
            "Error: Sanitizers can be enabled only with 'Debug' build\n"
            "Hint: Use 'cmake .. -DCMAKE_BUILD_TYPE=Debug'")
        return()
    endif()
    
    target_link_libraries(
        ${target}
            PRIVATE
                -fsanitize=${sanitizer}
    )
    
    if(${sanitizer} STREQUAL "address")
        target_link_libraries(
            ${target}
                PRIVATE
                    -fno-omit-frame-pointer
        )
    endif()
    
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if (${sanitizer} STREQUAL "undefined")
            target_link_libraries(
                ${target}
                    PRIVATE
                        -lubsan
            )
        elseif (${sanitizer} STREQUAL "thread")
            target_link_libraries(
                ${target}
                    PRIVATE
                        -ltsan
            )
        endif()
    endif()
endfunction()