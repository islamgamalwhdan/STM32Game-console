################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Math/Math_lib.c 

OBJS += \
./Core/Math/Math_lib.o 

C_DEPS += \
./Core/Math/Math_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Math/%.o Core/Math/%.su: ../Core/Math/%.c Core/Math/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Core/Math -I../Core/Mem_manger -I../Core/Graphics -I../Core/Graphics/fonts -I../Core/Graphics/Sprites -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Math

clean-Core-2f-Math:
	-$(RM) ./Core/Math/Math_lib.d ./Core/Math/Math_lib.o ./Core/Math/Math_lib.su

.PHONY: clean-Core-2f-Math

