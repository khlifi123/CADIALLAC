/*
 * interruption.c
 *
 *  Created on: Jan 26, 2024
 *      Author: m-ali.khlifi
 */

#include "interruption.h"
#include "gpio.h"
#include "tim.h"
#include "math.h"
extern volatile int CountMR1; // NOMBRE D IMPULSION ENCODEUR1
extern volatile int CountMR2; // NOMBRE D IMPULSION ENCODEUR2
extern volatile int CountMR3; // NOMBRE D IMPULSION ENCODEUR3
extern volatile int CountMR4; // NOMBRE D IMPULSION ENCODEUR4


int PinEncodeurVitesse1,PinEncodeurSens1;// DEUX INPUT ENCODEUR 1
int PinEncodeurVitesse2,PinEncodeurSens2;// DEUX INPUT ENCODEUR 2
int PinEncodeurVitesse3,PinEncodeurSens3;// DEUX INPUT ENCODEUR 3
int PinEncodeurVitesse4,PinEncodeurSens4;// DEUX INPUT ENCODEUR 4
int PinEncodeurVitesse5,PinEncodeurSens5;// DEUX INPUT ENCODEUR 5
int PinEncodeurVitesse6,PinEncodeurSens6;// DEUX INPUT ENCODEUR 6

double Interruption_1()
{
	PinEncodeurVitesse1= HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
	PinEncodeurSens1=HAL_GPIO_ReadPin(GPIOE, rotation1_Pin);

	if((PinEncodeurSens1&&PinEncodeurVitesse1)||(!PinEncodeurVitesse1&&!PinEncodeurSens1))
	{
		CountMR1-=1;
		if (CountMR1<0)
		    CountMR1=0;
	}else
	{

		CountMR1+=1;
    }
	//Course_Verin1=CountM1/9.50;//floor(CountM1*IMPULSION_TO_COURSE);
	return CountMR1;
}

double Interruption_2()
{                                  //compter le nomb de tours
	PinEncodeurVitesse2= HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);
	PinEncodeurSens2=HAL_GPIO_ReadPin(GPIOE, rotation2_Pin);

	if((PinEncodeurVitesse2&&PinEncodeurSens2)||(!PinEncodeurVitesse2&&!PinEncodeurSens2))
	{

		CountMR2-=1;

		if (CountMR2<0)
			CountMR2=0;
	}else CountMR2+=1;
	//Course_Verin2=floor(CountM2*IMPULSION_TO_COURSE);
	return CountMR2;
}
double Interruption_3()
{                                  //compter le nomb de tours
	PinEncodeurVitesse3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13);
	PinEncodeurSens3=HAL_GPIO_ReadPin(GPIOE, rotation3_Pin);

	if((PinEncodeurVitesse3&&PinEncodeurSens3)||(!PinEncodeurVitesse3&&!PinEncodeurSens3))
	{

		CountMR3-=1;

		if (CountMR3<0)
			CountMR3=0;
	}else
	{
		CountMR3+=1;
	}
	//Course_Verin3=floor(CountM3*IMPULSION_TO_COURSE);

	return CountMR3;
}

double Interruption_4()
{                                  //compter le nomb de tours
	PinEncodeurVitesse4= HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_14);
	PinEncodeurSens4=HAL_GPIO_ReadPin(GPIOE, rotation4_Pin);

	if((PinEncodeurVitesse4&&PinEncodeurSens4)||(!PinEncodeurVitesse4&&!PinEncodeurSens4))
	{
		CountMR4-=1;
		if (CountMR4<0)
			CountMR4=0;
	}else
	{
		CountMR4+=1;
	}
	//Course_Verin4=floor(CountM4*IMPULSION_TO_COURSE);

    return CountMR4;
}

