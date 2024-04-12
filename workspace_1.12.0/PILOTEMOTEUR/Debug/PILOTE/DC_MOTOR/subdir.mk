################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PILOTE/DC_MOTOR/DC_MOTOR.c \
../PILOTE/DC_MOTOR/DC_MOTOR_cfg.c 

OBJS += \
./PILOTE/DC_MOTOR/DC_MOTOR.o \
./PILOTE/DC_MOTOR/DC_MOTOR_cfg.o 

C_DEPS += \
./PILOTE/DC_MOTOR/DC_MOTOR.d \
./PILOTE/DC_MOTOR/DC_MOTOR_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
PILOTE/DC_MOTOR/%.o PILOTE/DC_MOTOR/%.su PILOTE/DC_MOTOR/%.cyclo: ../PILOTE/DC_MOTOR/%.c PILOTE/DC_MOTOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/m-ali.khlifi-ext/STM32CubeIDE/workspace_1.12.0/PILOTEMOTEUR/PILOTE/DC_MOTOR" -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PILOTE-2f-DC_MOTOR

clean-PILOTE-2f-DC_MOTOR:
	-$(RM) ./PILOTE/DC_MOTOR/DC_MOTOR.cyclo ./PILOTE/DC_MOTOR/DC_MOTOR.d ./PILOTE/DC_MOTOR/DC_MOTOR.o ./PILOTE/DC_MOTOR/DC_MOTOR.su ./PILOTE/DC_MOTOR/DC_MOTOR_cfg.cyclo ./PILOTE/DC_MOTOR/DC_MOTOR_cfg.d ./PILOTE/DC_MOTOR/DC_MOTOR_cfg.o ./PILOTE/DC_MOTOR/DC_MOTOR_cfg.su

.PHONY: clean-PILOTE-2f-DC_MOTOR

