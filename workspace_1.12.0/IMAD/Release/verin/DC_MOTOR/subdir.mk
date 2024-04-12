################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../verin/DC_MOTOR/DC_MOTOR.c \
../verin/DC_MOTOR/DC_MOTOR_cfg.c 

OBJS += \
./verin/DC_MOTOR/DC_MOTOR.o \
./verin/DC_MOTOR/DC_MOTOR_cfg.o 

C_DEPS += \
./verin/DC_MOTOR/DC_MOTOR.d \
./verin/DC_MOTOR/DC_MOTOR_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
verin/DC_MOTOR/%.o verin/DC_MOTOR/%.su verin/DC_MOTOR/%.cyclo: ../verin/DC_MOTOR/%.c verin/DC_MOTOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-verin-2f-DC_MOTOR

clean-verin-2f-DC_MOTOR:
	-$(RM) ./verin/DC_MOTOR/DC_MOTOR.cyclo ./verin/DC_MOTOR/DC_MOTOR.d ./verin/DC_MOTOR/DC_MOTOR.o ./verin/DC_MOTOR/DC_MOTOR.su ./verin/DC_MOTOR/DC_MOTOR_cfg.cyclo ./verin/DC_MOTOR/DC_MOTOR_cfg.d ./verin/DC_MOTOR/DC_MOTOR_cfg.o ./verin/DC_MOTOR/DC_MOTOR_cfg.su

.PHONY: clean-verin-2f-DC_MOTOR

