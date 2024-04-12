/*
 * File: DC_MOTOR_cfg.c
 * Driver Name: [[ DC MOTOR ]]
 * SW Layer:   verin
 * Created on:2023
 * Ver: 1.0
 * Author:     khlifi
 */

#include "DC_MOTOR.h"

const DC_MOTOR_CfgType DC_MOTOR_CfgParam[DC_MOTOR_UNITS] =
{
	// DC MOTOR 1 Configurations
    {
	    GPIOD,
		GPIOC,
		GPIO_PIN_3,//VINA1
		GPIO_PIN_0,//VINB1
		TIM2,
		TIM_CHANNEL_1,

	},// DC MOTOR 1 Configurations
    {
	    GPIOD,
		GPIOC,
		GPIO_PIN_4,//VINA1
		GPIO_PIN_1,//VINB1
		TIM2,
		TIM_CHANNEL_2,

	},// DC MOTOR 1 Configurations
    {
	    GPIOE,
		GPIOC,
		GPIO_PIN_2,//VINA1
		GPIO_PIN_2,//VINB1
		TIM2,
		TIM_CHANNEL_3,

	},// DC MOTOR 1 Configurations
    {
	    GPIOE,
		GPIOC,
		GPIO_PIN_3,//VINA1
		GPIO_PIN_3,//VINB1
		TIM2,
		TIM_CHANNEL_4,

	},

	{
		GPIOE,
		GPIOC,
		GPIO_PIN_4,//
		GPIO_PIN_4,//
		TIM3,
		TIM_CHANNEL_1,//PA9

	},
	{
			GPIOE,
			GPIOC,
			GPIO_PIN_5,//
			GPIO_PIN_5,//
			TIM3,
			TIM_CHANNEL_2,//PA9

		},

};
