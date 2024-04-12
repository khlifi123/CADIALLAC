/*
 * File: DC_MOTOR_cfg.c
 * Driver Name: [[ DC MOTOR ]]
 * SW Layer:   verin
 * Created on:2023
 * Ver: 1.0
 * Author:     khlifi
 */

#include "../DC_MOTOR/DC_MOTOR.h"

const DC_MOTOR_CfgType DC_MOTOR_CfgParam[DC_MOTOR_UNITS] =
{
	// DC MOTOR 1 Configurations
    {
	    GPIOC,
		GPIOC,
		GPIO_PIN_0,//VINA
		GPIO_PIN_1,//VINB
		TIM1,
		TIM_CHANNEL_1,//PA8

	},
	// DC MOTOR 2 Configurations
	{
		GPIOC,
		GPIOC,
		GPIO_PIN_3,//
		GPIO_PIN_2,//
		TIM1,
		TIM_CHANNEL_2,//PA9

	}
};
