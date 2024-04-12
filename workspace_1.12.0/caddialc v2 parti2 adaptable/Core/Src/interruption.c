/*
 * interruption.c
 *
 *  Created on: Feb 26, 2024
 *      Author: m-ali.khlifi
 */


#include "interruption.h"
#include "gpio.h"
#include "tim.h"
#include "math.h"
extern volatile int CountMR1; // NOMBRE D IMPULSION ENCODEUR1
extern volatile int CountMR2; // NOMBRE D IMPULSION ENCODEUR2



int PinEncodeurVitesse1,PinEncodeurSens1;// DEUX INPUT ENCODEUR 1
int PinEncodeurVitesse2,PinEncodeurSens2;// DEUX INPUT ENCODEUR 2


double Interruption_1()
{
	PinEncodeurVitesse1= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	PinEncodeurSens1=HAL_GPIO_ReadPin(GPIOC, rotation1_Pin);

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
	PinEncodeurVitesse2= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	PinEncodeurSens2=HAL_GPIO_ReadPin(GPIOC, rotation2_Pin);

	if((PinEncodeurVitesse2&&PinEncodeurSens2)||(!PinEncodeurVitesse2&&!PinEncodeurSens2))
	{

		CountMR2-=1;

		if (CountMR2<0)
			CountMR2=0;
	}else CountMR2+=1;
	//Course_Verin2=floor(CountM2*IMPULSION_TO_COURSE);
	return CountMR2;
}
