/*
 * File: DC_MOTOR.c
 * Driver Name: [[ DC MOTOR ]]
 * SW Layer:   verin
 * Created on:2023
 * Ver: 1.0
 * Author:     khlifi
 */

#include "DC_MOTOR.h"
#include "DC_MOTOR_cfg.h"
#include "main.h"

void DC_MOTOR_Init(uint8_t au8_MOTOR_Instance) {

	/*--------[ Configure The 2 Direction Control GPIO Pins ]-------*/
	GPIO_InitTypeDef GPIO_InitStruct = {0};


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


    if (DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance == TIM2) {
        // Configuration for TIM2
    	   RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
    	   RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
    	   RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;

    	   GPIOA->MODER|=GPIO_MODER_MODER0_1;//PA0
    	   GPIOA->AFR[0]|=0X00000001;
    	   TIM2->CCMR1&=~TIM_CCMR1_CC1S;
		   TIM2->CCMR1|=TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1;
		   TIM2->CCMR1|=TIM_CCMR1_OC1PE;
		   TIM2->CCER|=TIM_CCER_CC1E;

    	   GPIOB->MODER|=GPIO_MODER_MODER3_1;//PB3
    	   GPIOB->AFR[0]|=0X00001000;
    	   TIM2->CCMR1&=~TIM_CCMR1_CC2S;
    	   TIM2->CCMR1|=TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1;
    	   TIM2->CCMR1|=TIM_CCMR1_OC2PE;
    	   TIM2->CCER|=TIM_CCER_CC2E;

		   GPIOB->MODER|=GPIO_MODER_MODER10_1;//PB10
		   GPIOB->AFR[1]|=0X00000100;
		   TIM2->CCMR2&=~TIM_CCMR2_CC3S;
		   TIM2->CCMR2|=TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1;
		   TIM2->CCMR2|=TIM_CCMR2_OC3PE;
		   TIM2->CCER|=TIM_CCER_CC3E;

		   GPIOB->MODER|=GPIO_MODER_MODER11_1;//PB11
		   GPIOB->AFR[1]|=0X00001000;
		   TIM2->CCMR2&=~TIM_CCMR2_CC4S;
		   TIM2->CCMR2|=TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1;
		   TIM2->CCMR2|=TIM_CCMR2_OC4PE;
		   TIM2->CCER|=TIM_CCER_CC4E;

    } else if (DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance == TIM3 && DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH==TIM_CHANNEL_1)
    {
        // Configuration for TIM3
    	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
    	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

       	// Configurer le mode alternatif pour PA6
       	GPIOA->MODER |= GPIO_MODER_MODER6_1;
       	GPIOA->AFR[0] |= 0X02000000; // AF2
       	// Configurer le canal 4 comme sortie PWM
       	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S; // Sélectionner la sortie CC4
       	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // Mode PWM1
    	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    	TIM3->CCER |= TIM_CCER_CC1E;
    }else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance == TIM3 && DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH==TIM_CHANNEL_3)
    {


    		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
    	    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
     	// Configurer le mode alternatif pour PA7
           	GPIOB->MODER |= GPIO_MODER_MODER0_1;
           	GPIOB->AFR[0] |= 0X00000020; // AF2

           	TIM3->CCMR2 &= ~TIM_CCMR2_CC3S; //
           	TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; //
        	TIM3->CCMR2 |= TIM_CCMR2_OC3PE;
        	TIM3->CCER |= TIM_CCER_CC3E;
    	}


    DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->PSC = 53;
    DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->ARR = 100;
    DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CR1 |= TIM_CR1_ARPE;
    DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CR1 |= TIM_CR1_CEN;
}

void DC_MOTOR_Start(uint8_t au8_MOTOR_Instance,uint8_t au8_DIR, uint16_t au16_SPEED)
{




	if(au8_DIR == 1)
		{
			HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 1);
			HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 0);

		}
	else if(au8_DIR == 0)
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

void DC_MOTOR_Frein(uint8_t au8_MOTOR_Instance){

	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR1_PIN, 0);
	HAL_GPIO_WritePin(DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_GPIO, DC_MOTOR_CfgParam[au8_MOTOR_Instance].DIR2_PIN, 0);
	if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_1)
		{
			DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR1 = 100;
		}
		else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_2)
		{
			DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR2 = 100;
		}
		else if(DC_MOTOR_CfgParam[au8_MOTOR_Instance].PWM_TIM_CH == TIM_CHANNEL_3)
		{
			DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR3 = 100;
		}
		else
		{
			DC_MOTOR_CfgParam[au8_MOTOR_Instance].TIM_Instance->CCR4 = 100;
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
