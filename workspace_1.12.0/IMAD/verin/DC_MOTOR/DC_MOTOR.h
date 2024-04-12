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

#include "stm32f4xx_hal.h"

// DC Motor Rotation Directions
#define DIR_CW    0
#define DIR_CCW   1



// The Number OF DC MOTORs To Be Used In The Project
#define DC_MOTOR_UNITS  2

typedef struct
{
	GPIO_TypeDef * DIR1_GPIO;
	GPIO_TypeDef * DIR2_GPIO;
	uint16_t       DIR1_PIN;
	uint16_t       DIR2_PIN;
	TIM_TypeDef*   TIM_Instance;
	uint32_t       PWM_TIM_CH;//rapport cycl

}DC_MOTOR_CfgType;


/*-----[ Prototypes For All Functions ]-----*/

void DC_MOTOR_Init(uint8_t au8_MOTOR_Instance);
void DC_MOTOR_Start(uint8_t au8_MOTOR_Instance, uint8_t au8_DIR, uint16_t au16_SPEED);
void DC_MOTOR_Set_Speed(uint8_t au8_MOTOR_Instance, uint16_t au16_SPEED);
void  DC_MOTOR_Set_Direction(uint8_t au8_MOTOR_Instance, uint8_t au8_DIR);
void DC_Stand_BY(uint8_t au8_MOTOR_Instance);
void Frein(uint8_t au8_MOTOR_Instance);


#endif /* DC_MOTOR_H_ */
