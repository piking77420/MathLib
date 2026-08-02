if(PROCESSOR MATCHES "^(x86_64|amd64|x64)$")
    message(STATUS "Target architecture: x86-64")
    set(CPU_X86_64 TRUE)

elseif(PROCESSOR MATCHES "^(x86|i[3-6]86)$")
    message(STATUS "Target architecture: x86")
    set(CPU_X86 TRUE)

elseif(PROCESSOR MATCHES "^(aarch64|arm64)$")
    message(STATUS "Target architecture: ARM64")
    set(CPU_ARM64 TRUE)

elseif(PROCESSOR MATCHES "^arm")
    message(STATUS "Target architecture: ARM")
    set(CPU_ARM TRUE)

else()
    message(WARNING "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()