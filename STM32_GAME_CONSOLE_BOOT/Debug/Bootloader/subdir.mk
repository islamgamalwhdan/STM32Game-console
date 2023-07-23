################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/Bootloader.c \
../Bootloader/main.c 

OBJS += \
./Bootloader/Bootloader.o \
./Bootloader/main.o 

C_DEPS += \
./Bootloader/Bootloader.d \
./Bootloader/main.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/%.o Bootloader/%.su: ../Bootloader/%.c Bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Bootloader -I../Core/Graphics -I../Core/Graphics/Sprites -I../Core/Graphics/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Bootloader

clean-Bootloader:
	-$(RM) ./Bootloader/Bootloader.d ./Bootloader/Bootloader.o ./Bootloader/Bootloader.su ./Bootloader/main.d ./Bootloader/main.o ./Bootloader/main.su

.PHONY: clean-Bootloader

