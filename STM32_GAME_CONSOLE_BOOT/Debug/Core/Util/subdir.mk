################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Util/auxiliary.c \
../Core/Util/printf.c 

OBJS += \
./Core/Util/auxiliary.o \
./Core/Util/printf.o 

C_DEPS += \
./Core/Util/auxiliary.d \
./Core/Util/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Util/%.o Core/Util/%.su: ../Core/Util/%.c Core/Util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Bootloader -I../Core/Graphics -I../Core/Graphics/Sprites -I../Core/Graphics/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Util

clean-Core-2f-Util:
	-$(RM) ./Core/Util/auxiliary.d ./Core/Util/auxiliary.o ./Core/Util/auxiliary.su ./Core/Util/printf.d ./Core/Util/printf.o ./Core/Util/printf.su

.PHONY: clean-Core-2f-Util

