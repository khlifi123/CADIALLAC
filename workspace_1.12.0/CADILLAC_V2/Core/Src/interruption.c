/*
 * interruption.c
 *
 *  Created on: Nov 27, 2023
 *      Author: m-ali.khlifi
 */


#include "interruption.h"
#include "gpio.h"
#include "tim.h"
#include "math.h"
extern volatile int CountM1; // NOMBRE D IMPULSION ENCODEUR1
extern volatile int CountM2; // NOMBRE D IMPULSION ENCODEUR2
extern volatile int CountM3; // NOMBRE D IMPULSION ENCODEUR3
extern volatile int CountM4; // NOMBRE D IMPULSION ENCODEUR4
extern volatile int CountM5; // NOMBRE D IMPULSION ENCODEUR5
extern volatile int CountM6; // NOMBRE D IMPULSION ENCODEUR6

int PinEncodeurVitesse1,PinEncodeurSens1;// DEUX INPUT ENCODEUR 1
int PinEncodeurVitesse2,PinEncodeurSens2;// DEUX INPUT ENCODEUR 2
int PinEncodeurVitesse3,PinEncodeurSens3;// DEUX INPUT ENCODEUR 3
int PinEncodeurVitesse4,PinEncodeurSens4;// DEUX INPUT ENCODEUR 4
int PinEncodeurVitesse5,PinEncodeurSens5;// DEUX INPUT ENCODEUR 5
int PinEncodeurVitesse6,PinEncodeurSens6;// DEUX INPUT ENCODEUR 6

double Interruption_1()
{
	PinEncodeurVitesse1= HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
	PinEncodeurSens1=HAL_GPIO_ReadPin(GPIOC, rotation1_Pin);

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
	PinEncodeurVitesse2= HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
	PinEncodeurSens2=HAL_GPIO_ReadPin(GPIOC, rotation2_Pin);

	if((PinEncodeurSens2&&PinEncodeurVitesse2)||(!PinEncodeurVitesse2&&!PinEncodeurSens2))
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
	PinEncodeurVitesse3=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
	PinEncodeurSens3=HAL_GPIO_ReadPin(GPIOA, rotation3_Pin);

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
	PinEncodeurVitesse4= HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);
	PinEncodeurSens4=HAL_GPIO_ReadPin(GPIOD, rotation4_Pin);//PD5

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
	PinEncodeurVitesse5=HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13);
	PinEncodeurSens5=HAL_GPIO_ReadPin(GPIOD, rotation5_Pin);//PD6

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
	PinEncodeurVitesse6= HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_14);
	PinEncodeurSens6=HAL_GPIO_ReadPin(GPIOD, rotation6_Pin);//PD7

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

