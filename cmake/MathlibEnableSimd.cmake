function(mathlib_enable_simd target level)
    string(TOUPPER "${level}" level_upper)

    set(simd_option "")

    if(MSVC)
        if(level_upper STREQUAL "SSE2")
            # SSE2 is the baseline for MSVC x64.
            # For 32-bit x86, you may need /arch:SSE2.

        elseif(level_upper STREQUAL "AVX")
            set(simd_option /arch:AVX)

        elseif(level_upper STREQUAL "AVX2")
            set(simd_option /arch:AVX2)

        elseif(level_upper STREQUAL "AVX512F")
            set(simd_option /arch:AVX512)

        else()
            message(FATAL_ERROR
                "Unsupported SIMD level '${level}' for MSVC"
            )
        endif()

    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        if (CPU_ARM64)
            if(level_upper STREQUAL "NEON")
            # NEON is always available on ARM64/AArch64.
            set(simd_option "")

            elseif(level_upper STREQUAL "SVE")
                set(simd_option -march=armv8.2-a+sve)

            else()
                message(FATAL_ERROR
                    "Unsupported ARM64 SIMD level '${level}'. "
                    "Supported levels: NEON, SVE"
            )
            endif()
        endif()
        if (CPU_X86_64)
            if(level_upper STREQUAL "SSE2")
            set(simd_option -msse2)

            elseif(level_upper STREQUAL "AVX")
                set(simd_option -mavx)

            elseif(level_upper STREQUAL "AVX2")
                set(simd_option -mavx2)

            elseif(level_upper STREQUAL "AVX512F")
                set(simd_option -mavx512f)

            else()
                message(FATAL_ERROR
                    "Unsupported SIMD level '${level}' for "
                    "${CMAKE_CXX_COMPILER_ID}"
                )
            endif()
        endif()        
    else()
        message(FATAL_ERROR
            "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}"
        )
    endif()

    target_compile_definitions(
        ${target}
        PUBLIC
            "MATHLIB_SIMD_LEVEL_${level_upper}=1"
    )

    if(simd_option)
        target_compile_options(
            ${target}
            PRIVATE
                ${simd_option}
        )
    endif()
endfunction()