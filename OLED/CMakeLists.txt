cmake_minimum_required(VERSION 3.20)

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0                   "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS               "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3                   "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4                   "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7                   "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33                  "-mcpu=cortex-m33")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "mspm0_oled")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "${CMAKE_CURRENT_SOURCE_DIR}/MSPM0L1306.ld")
set (MCPU                     ${MCPU_CORTEX_M0PLUS})
set (MFPU                     "")
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          ${RUNTIME_LIBRARY_REDUCED_C})
set (RUNTIME_LIBRARY_SYSCALLS ${RUNTIME_LIBRARY_SYSCALLS_MINIMAL})
set (CMAKE_BUILD_TYPE         Debug)

file (GLOB PROJECT_SOURCES
    BSP/src/*.c
    Core/src/*.c
    Driver/ti/driverlib/*.c
    Driver/ti/driverlib/m0p/*.c
    Driver/ti/driverlib/m0p/sysctl/*.c
	)

set (PROJECT_DEFINES
	# LIST COMPILER DEFINITIONS HERE
	__MSPM0L1306__
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    BSP/Inc
    Core/Inc
    Driver/CMSIS/Core/Include
    Driver
    )

############ MODIFY ACCORDING TO REQUIREMENTS) ########################

#######################################################################
set(CMAKE_TOOLCHAIN_FILE toolchains/gcc-arm-none-eabi.cmake)
################## PROJECT SETUP ######################################
project(${PROJECT_NAME} C ASM)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Og -g3 -ggdb -ffunction-sections -fdata-sections -fstack-usage")
elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Ofast -ffunction-sections -fdata-sections -fstack-usage")
endif()
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")