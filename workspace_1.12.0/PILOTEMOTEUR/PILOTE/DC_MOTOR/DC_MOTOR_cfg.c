/*
 * File: DC_MOTOR_cfg.c
 * Driver Name: [[ DC MOTOR ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#include "DC_MOTOR.h"

const DC_MOTOR_CfgType DC_MOTOR_CfgParam[6] =
{


		    {GPIOD, GPIOC, GPIO_PIN_3, GPIO_PIN_0, TIM2, TIM_CHANNEL_1},
		    {GPIOD, GPIOC, GPIO_PIN_4, GPIO_PIN_1, TIM2, TIM_CHANNEL_2},
		    {GPIOE, GPIOC, GPIO_PIN_2, GPIO_PIN_2, TIM2, TIM_CHANNEL_3},
		    {GPIOE, GPIOC, GPIO_PIN_3, GPIO_PIN_3, TIM2, TIM_CHANNEL_4},
			{GPIOE, GPIOC, GPIO_PIN_4, GPIO_PIN_4, TIM3, TIM_CHANNEL_1},
		    {GPIOE, GPIOC, GPIO_PIN_5, GPIO_PIN_5, TIM3, TIM_CHANNEL_2}




};



