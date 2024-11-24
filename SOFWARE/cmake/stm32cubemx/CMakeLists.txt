cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32G431xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Inc
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/include
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/CMSIS/Device/ST/STM32G4xx/Include
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/CMSIS/Include
)

target_sources(stm32cubemx INTERFACE
    ../../Core/Src/main.c
    ../../Core/Src/gpio.c
    ../../Core/Src/app_freertos.c
    ../../Core/Src/adc.c
    ../../Core/Src/i2c.c
    ../../Core/Src/tim.c
    ../../Core/Src/usart.c
    ../../Core/Src/stm32g4xx_it.c
    ../../Core/Src/stm32g4xx_hal_msp.c
    ../../Core/Src/stm32g4xx_hal_timebase_tim.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_adc_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c
    ../../Core/Src/system_stm32g4xx.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/list.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    C:/Users/aliou/STM32Cube/Repository/STM32Cube_FW_G4_V1.6.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32g431xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


