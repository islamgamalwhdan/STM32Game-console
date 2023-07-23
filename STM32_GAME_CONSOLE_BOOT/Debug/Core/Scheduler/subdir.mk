################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Scheduler/Scheduler.c 

OBJS += \
./Core/Scheduler/Scheduler.o 

C_DEPS += \
./Core/Scheduler/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Scheduler/%.o Core/Scheduler/%.su: ../Core/Scheduler/%.c Core/Scheduler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Bootloader -I../Core/Graphics -I../Core/Graphics/Sprites -I../Core/Graphics/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Scheduler

clean-Core-2f-Scheduler:
	-$(RM) ./Core/Scheduler/Scheduler.d ./Core/Scheduler/Scheduler.o ./Core/Scheduler/Scheduler.su

.PHONY: clean-Core-2f-Scheduler

