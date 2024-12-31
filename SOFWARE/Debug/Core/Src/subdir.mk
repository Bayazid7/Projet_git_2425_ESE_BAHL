################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADXL343.c \
../Core/Src/GP2Y0E02A.c \
../Core/Src/LIDAR.c \
../Core/Src/MoteurPWM.c \
../Core/Src/adc.c \
../Core/Src/app_freertos.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/lidar_X2_driver.c \
../Core/Src/main.c \
../Core/Src/shell.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_hal_timebase_tim.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/ADXL343.o \
./Core/Src/GP2Y0E02A.o \
./Core/Src/LIDAR.o \
./Core/Src/MoteurPWM.o \
./Core/Src/adc.o \
./Core/Src/app_freertos.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/lidar_X2_driver.o \
./Core/Src/main.o \
./Core/Src/shell.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_hal_timebase_tim.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/ADXL343.d \
./Core/Src/GP2Y0E02A.d \
./Core/Src/LIDAR.d \
./Core/Src/MoteurPWM.d \
./Core/Src/adc.d \
./Core/Src/app_freertos.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/lidar_X2_driver.d \
./Core/Src/main.d \
./Core/Src/shell.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_hal_timebase_tim.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADXL343.cyclo ./Core/Src/ADXL343.d ./Core/Src/ADXL343.o ./Core/Src/ADXL343.su ./Core/Src/GP2Y0E02A.cyclo ./Core/Src/GP2Y0E02A.d ./Core/Src/GP2Y0E02A.o ./Core/Src/GP2Y0E02A.su ./Core/Src/LIDAR.cyclo ./Core/Src/LIDAR.d ./Core/Src/LIDAR.o ./Core/Src/LIDAR.su ./Core/Src/MoteurPWM.cyclo ./Core/Src/MoteurPWM.d ./Core/Src/MoteurPWM.o ./Core/Src/MoteurPWM.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/lidar_X2_driver.cyclo ./Core/Src/lidar_X2_driver.d ./Core/Src/lidar_X2_driver.o ./Core/Src/lidar_X2_driver.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/shell.cyclo ./Core/Src/shell.d ./Core/Src/shell.o ./Core/Src/shell.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_hal_timebase_tim.cyclo ./Core/Src/stm32g4xx_hal_timebase_tim.d ./Core/Src/stm32g4xx_hal_timebase_tim.o ./Core/Src/stm32g4xx_hal_timebase_tim.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

