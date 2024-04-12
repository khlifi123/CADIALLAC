/*
 * File: DC_MOTOR.h
 * Driver Name: [[ DC MOTOR ]]
 * SW Layer:   verin
 * Created on:2023
 * Ver: 1.0
 * Author:     khlifi


 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define HAL_TIM_MODULE_ENABLED

#include "stm32f7xx_hal.h"



/*-----[ Prototypes For All Functions ]-----*/

void DC_MOTOR_Init(uint8_t au8_MOTOR_Instance);
void DC_MOTOR_Start(uint8_t au8_MOTOR_Instance,uint8_t au8_DIR, uint16_t au16_SPEED);
void DC_MOTOR_Stop(uint8_t au8_MOTOR_Instance);
void DC_MOTOR_Frein(uint8_t au8_MOTOR_Instance);


#endif /* DC_MOTOR_H_ */
