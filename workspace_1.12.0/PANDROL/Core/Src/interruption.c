/*
 * interruption.c
 *
 *  Created on: May 15, 2023
 *      Author: m-ali.khlifi-ext
 */
#include "interruption.h"
#include "gpio.h"
#include "stdbool.h"
#include "tim.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

#define IMPULSION_TO_COURSE  230.00/2205.70

extern int CountM1; // NOMBRE D IMPULSION ENCODEUR1
extern int CountM2; // NOMBRE D IMPULSION ENCODEUR2
extern int CountM3; // NOMBRE D IMPULSION ENCODEUR3
extern int CountM4; // NOMBRE D IMPULSION ENCODEUR4
extern int CountM5; // NOMBRE D IMPULSION ENCODEUR5
extern int CountM6; // NOMBRE D IMPULSION ENCODEUR6

int PinEncodeurVitesse1,PinEncodeurSens1;// DEUX INPUT ENCODEUR 1
int PinEncodeurVitesse2,PinEncodeurSens2;// DEUX INPUT ENCODEUR 2
int PinEncodeurVitesse3,PinEncodeurSens3;// DEUX INPUT ENCODEUR 3
int PinEncodeurVitesse4,PinEncodeurSens4;// DEUX INPUT ENCODEUR 4
int PinEncodeurVitesse5,PinEncodeurSens5;// DEUX INPUT ENCODEUR 5
int PinEncodeurVitesse6,PinEncodeurSens6;// DEUX INPUT ENCODEUR 6

double Interruption_1()
{
	PinEncodeurVitesse1= GPIOA->IDR&=0x0001;// HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	PinEncodeurSens1=GPIOC->IDR&=0x0400;//HAL_GPIO_ReadPin(GPIOC, rotation1_Pin);

	if((PinEncodeurSens1&&PinEncodeurVitesse1)||(!PinEncodeurVitesse1&&!PinEncodeurSens1))
	{
		CountM1-=1;
		if (CountM1<0)
		    CountM1=0;
	}else
	{

		CountM1+=1;
    }
	//Course_Verin1=CountM1/9.50;//floor(CountM1*IMPULSION_TO_COURSE);
	return CountM1;
}

double Initerruption_2()
{                                  //compter le nomb de tours
	PinEncodeurVitesse2= GPIOC->IDR&=0x0080;     //HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);//TIM12
	PinEncodeurSens2=GPIOC->IDR&=0x0800;       //HAL_GPIO_ReadPin(GPIOC, rotation2_Pin);

	if((PinEncodeurVitesse2&&PinEncodeurSens2)||(!PinEncodeurVitesse2&&!PinEncodeurSens2))
	{

		CountM2-=1;

		if (CountM2<0)
			CountM2=0;
	}else CountM2+=1;
	//Course_Verin2=floor(CountM2*IMPULSION_TO_COURSE);
	return CountM2;
}
double Interruption_3()
{                                  //compter le nomb de tours
	PinEncodeurVitesse3=GPIOB->IDR&=0x0040; //HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
	PinEncodeurSens3=GPIOA->IDR&=0x8000;//HAL_GPIO_ReadPin(GPIOA, rotation3_Pin);

	if((PinEncodeurVitesse3&&PinEncodeurSens3)||(!PinEncodeurVitesse3&&!PinEncodeurSens3))
	{

		CountM3-=1;

		if (CountM3<0)
			CountM3=0;
	}else
	{
		CountM3+=1;
	}
	//Course_Verin3=floor(CountM3*IMPULSION_TO_COURSE);

	return CountM3;
}

double Interruption_4()
{                                  //compter le nomb de tours
	PinEncodeurVitesse4= GPIOB->IDR&=0x0080;//HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
	PinEncodeurSens4=GPIOC->IDR&=0x2000;//HAL_GPIO_ReadPin(GPIOC, rotation4_Pin);

	if((PinEncodeurVitesse4&&PinEncodeurSens4)||(!PinEncodeurVitesse4&&!PinEncodeurSens4))
	{
		CountM4-=1;
		if (CountM4<0)
			CountM4=0;
	}else
	{
		CountM4+=1;
	}
	//Course_Verin4=floor(CountM4*IMPULSION_TO_COURSE);

    return CountM4;
}
double Interruption_5()
{                                  //compter le nomb de tours
	PinEncodeurVitesse5= GPIOB->IDR&=0x0100;//HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
	PinEncodeurSens5=GPIOB->IDR&=0x0004;//HAL_GPIO_ReadPin(GPIOB, rotation5_Pin);

	if((PinEncodeurVitesse5&&PinEncodeurSens5)||(!PinEncodeurVitesse5&&!PinEncodeurSens5))
	{

		CountM5-=1;
		if (CountM5<0)
			CountM5=0;
	}else
	{
		CountM5+=1;
	}
	//Course_Verin5=floor(CountM5*IMPULSION_TO_COURSE);

    return CountM5;
}
double Interruption_6()
{                                  //compter le nomb de tours
	PinEncodeurVitesse6= GPIOB->IDR&=0x0200;//HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
	PinEncodeurSens6=GPIOB->IDR&=0x0400;//HAL_GPIO_ReadPin(GPIOB, rotation6_Pin);

	if((PinEncodeurVitesse6&&PinEncodeurSens6)||(!PinEncodeurVitesse6&&!PinEncodeurSens6))
	{

		CountM6-=1;
		if (CountM6<0)
			CountM6=0;
	}else
	{
		CountM6+=1;
	}
	//Course_Verin6=floor(CountM6*IMPULSION_TO_COURSE);

    return CountM6;
}

