################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VE/DC_MOTOR.c \
../VE/DC_MOTOR_cfg.c 

OBJS += \
./VE/DC_MOTOR.o \
./VE/DC_MOTOR_cfg.o 

C_DEPS += \
./VE/DC_MOTOR.d \
./VE/DC_MOTOR_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
VE/%.o VE/%.su VE/%.cyclo: ../VE/%.c VE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/m-ali.khlifi-ext/STM32CubeIDE/workspace_1.12.0/last/VE" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-VE

clean-VE:
	-$(RM) ./VE/DC_MOTOR.cyclo ./VE/DC_MOTOR.d ./VE/DC_MOTOR.o ./VE/DC_MOTOR.su ./VE/DC_MOTOR_cfg.cyclo ./VE/DC_MOTOR_cfg.d ./VE/DC_MOTOR_cfg.o ./VE/DC_MOTOR_cfg.su

.PHONY: clean-VE

