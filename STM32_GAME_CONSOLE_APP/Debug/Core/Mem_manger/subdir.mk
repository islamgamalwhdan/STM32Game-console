################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Mem_manger/umm_malloc.c 

OBJS += \
./Core/Mem_manger/umm_malloc.o 

C_DEPS += \
./Core/Mem_manger/umm_malloc.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Mem_manger/%.o Core/Mem_manger/%.su: ../Core/Mem_manger/%.c Core/Mem_manger/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Core/Math -I../Core/Mem_manger -I../Core/Graphics -I../Core/Graphics/fonts -I../Core/Graphics/Sprites -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Mem_manger

clean-Core-2f-Mem_manger:
	-$(RM) ./Core/Mem_manger/umm_malloc.d ./Core/Mem_manger/umm_malloc.o ./Core/Mem_manger/umm_malloc.su

.PHONY: clean-Core-2f-Mem_manger

