################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PILOTE2/DC_MOTOR2/DC_MOTOR2.c \
../PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.c 

OBJS += \
./PILOTE2/DC_MOTOR2/DC_MOTOR2.o \
./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.o 

C_DEPS += \
./PILOTE2/DC_MOTOR2/DC_MOTOR2.d \
./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
PILOTE2/DC_MOTOR2/%.o PILOTE2/DC_MOTOR2/%.su PILOTE2/DC_MOTOR2/%.cyclo: ../PILOTE2/DC_MOTOR2/%.c PILOTE2/DC_MOTOR2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"C:/Users/m-ali.khlifi-ext/STM32CubeIDE/workspace_1.12.0/PILOTEMOTEUR/PILOTE/DC_MOTOR" -I"C:/Users/m-ali.khlifi-ext/STM32CubeIDE/workspace_1.12.0/PILOTEMOTEUR/PILOTE2/DC_MOTOR2" -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-PILOTE2-2f-DC_MOTOR2

clean-PILOTE2-2f-DC_MOTOR2:
	-$(RM) ./PILOTE2/DC_MOTOR2/DC_MOTOR2.cyclo ./PILOTE2/DC_MOTOR2/DC_MOTOR2.d ./PILOTE2/DC_MOTOR2/DC_MOTOR2.o ./PILOTE2/DC_MOTOR2/DC_MOTOR2.su ./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.cyclo ./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.d ./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.o ./PILOTE2/DC_MOTOR2/DC_MOTOR2_cfg.su

.PHONY: clean-PILOTE2-2f-DC_MOTOR2

