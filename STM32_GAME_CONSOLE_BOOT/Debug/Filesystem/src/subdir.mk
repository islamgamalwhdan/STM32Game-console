################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Filesystem/src/ccsbcs.c \
../Filesystem/src/diskio.c \
../Filesystem/src/fatfs.c \
../Filesystem/src/fatfs_sd.c \
../Filesystem/src/ff.c \
../Filesystem/src/ff_gen_drv.c \
../Filesystem/src/syscall.c \
../Filesystem/src/user_diskio.c 

OBJS += \
./Filesystem/src/ccsbcs.o \
./Filesystem/src/diskio.o \
./Filesystem/src/fatfs.o \
./Filesystem/src/fatfs_sd.o \
./Filesystem/src/ff.o \
./Filesystem/src/ff_gen_drv.o \
./Filesystem/src/syscall.o \
./Filesystem/src/user_diskio.o 

C_DEPS += \
./Filesystem/src/ccsbcs.d \
./Filesystem/src/diskio.d \
./Filesystem/src/fatfs.d \
./Filesystem/src/fatfs_sd.d \
./Filesystem/src/ff.d \
./Filesystem/src/ff_gen_drv.d \
./Filesystem/src/syscall.d \
./Filesystem/src/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
Filesystem/src/%.o Filesystem/src/%.su: ../Filesystem/src/%.c Filesystem/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Core/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Core/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Core/Drivers/CMSIS/Include -I../Filesystem/inc -I../Core/Scheduler -I../Core/Input -I../Core/Util -I../Core/HW_specific -I../Bootloader -I../Core/Graphics -I../Core/Graphics/Sprites -I../Core/Graphics/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Filesystem-2f-src

clean-Filesystem-2f-src:
	-$(RM) ./Filesystem/src/ccsbcs.d ./Filesystem/src/ccsbcs.o ./Filesystem/src/ccsbcs.su ./Filesystem/src/diskio.d ./Filesystem/src/diskio.o ./Filesystem/src/diskio.su ./Filesystem/src/fatfs.d ./Filesystem/src/fatfs.o ./Filesystem/src/fatfs.su ./Filesystem/src/fatfs_sd.d ./Filesystem/src/fatfs_sd.o ./Filesystem/src/fatfs_sd.su ./Filesystem/src/ff.d ./Filesystem/src/ff.o ./Filesystem/src/ff.su ./Filesystem/src/ff_gen_drv.d ./Filesystem/src/ff_gen_drv.o ./Filesystem/src/ff_gen_drv.su ./Filesystem/src/syscall.d ./Filesystem/src/syscall.o ./Filesystem/src/syscall.su ./Filesystem/src/user_diskio.d ./Filesystem/src/user_diskio.o ./Filesystem/src/user_diskio.su

.PHONY: clean-Filesystem-2f-src

