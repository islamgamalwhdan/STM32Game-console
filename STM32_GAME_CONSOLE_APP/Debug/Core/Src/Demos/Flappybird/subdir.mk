################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Demos/Flappybird/main.c 

OBJS += \
./Core/Src/Demos/Flappybird/main.o 

C_DEPS += \
./Core/Src/Demos/Flappybird/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Demos/Flappybird/%.o Core/Src/Demos/Flappybird/%.su: ../Core/Src/Demos/Flappybird/%.c Core/Src/Demos/Flappybird/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../FATFS/Target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Demos-2f-Flappybird

clean-Core-2f-Src-2f-Demos-2f-Flappybird:
	-$(RM) ./Core/Src/Demos/Flappybird/main.d ./Core/Src/Demos/Flappybird/main.o ./Core/Src/Demos/Flappybird/main.su

.PHONY: clean-Core-2f-Src-2f-Demos-2f-Flappybird

