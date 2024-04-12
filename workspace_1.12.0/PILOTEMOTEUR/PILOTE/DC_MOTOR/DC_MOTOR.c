/*
 * File: DC_MOTOR.c
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
#include "DC_MOTOR_cfg.h"
#include "main.h"
#include "tim.h"
void DC_MOTOR_Init(uint8_t au8_MOTOR_Instance)
{
	  MX_TIM2_Init();
	  MX_TIM3_Init();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    //TIM_MasterConfigTypeDef sMasterConfig = {0};
  //  TIM_OC_InitTypeDef sConfigOC = {0};
    //TIM_HandleTypeDef htim;

	/*--------[ Configure The 2 Direction Control GPIO Pins ]-------*/

    if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO == GPIOA || DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO == GPIOA)
    {
    	__HAL_RCC_GPIOA_CLK_ENABLE();
    }
    else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO == GPIOB || DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO == GPIOB)
    {
    	__HAL_RCC_GPIOB_CLK_ENABLE();
    }
    else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO == GPIOC || DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
    else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO == GPIOD || DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO == GPIOD)
    {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO == GPIOE || DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO == GPIOE)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
	GPIO_InitStruct.Pin = DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull =GPIO_PULLDOWN ;

	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, &GPIO_InitStruct);
	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 0);
	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 0);
//////////////////


	  /* USER CODE BEGIN TIM3_Init 1 */


}


void DC_MOTOR_Start(uint8_t au8_MOTOR_Instance, uint8_t au8_DIR, uint16_t au16_SPEED)
{
	/* Write To The 2 Direction Control Pins */
	if(au8_DIR == DIR_CW)
	{
		HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 1);
		HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 0);
	}
	else if(au8_DIR == DIR_CCW)
	{
		HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 0);
		HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 1);
	}

	/* Write The Speed Value To The PWM CH DutyCycle Register */
	if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_1)
	{

		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR1 = au16_SPEED;
	}
	else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_2)
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR2 = au16_SPEED;
	}
	else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_3)
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR3 = au16_SPEED;
	}
	else
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR4 = au16_SPEED;
	}
}





void DC_MOTOR_Stop(uint8_t au8_MOTOR_Instance)
{
	/* Write To The 2 Direction Control Pins */
	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 0);
	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 0);

	/* Write ZERO To The PWM Ch DutyCycle Register */
	if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_1)
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR1 = 0;
	}
	else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_2)
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR2 = 0;
	}
	else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_3)
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR3 = 0;
	}
	else
	{
		DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR4 = 0;
	}
}

