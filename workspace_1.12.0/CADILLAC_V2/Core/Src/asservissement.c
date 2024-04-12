/*
 * asservissement.c
 *
 *  Created on: Nov 27, 2023
 *      Author: m-ali.khlifi
 */


#include "asservissement.h"
#include "main.h"
#include"stdio.h"
#include"gpio.h"
#include"stdlib.h"

#define PWM_PERIOD  100
#define DEL 5

// Déclarer des pointeurs pour stocker les valeurs dynamiquement
float TensionMt1;
float Last_TesnionMt1;
float Last_ErreurMt1;

float TensionMt2;
float Last_TesnionMt2;
float Last_ErreurMt2;

float TensionMt3;
float Last_TesnionMt3;
float Last_ErreurMt3;

float TensionMt4;
float Last_TesnionMt4;
float Last_ErreurMt4;

float TensionMt5;
float Last_TesnionMt5;
float Last_ErreurMt5;

float TensionMt6;
float Last_TesnionMt6;
float Last_ErreurMt6;
extern uint8_t tens;

extern float vitesseRef1 ;            // VITESSE DE REFERNCE POUR L ASSERVISSEMENT
extern float vitesseRef3 ;
extern float vitesseRef2 ;





void Regulation_Mt1( float vitessem1,float vitessem6, float vf,float tensionMax)//reguler vitesse1 %vitesse reference et synchroniser avec vitesse2
{

	   float ErreurMt1=vf-vitessem1;
	   TensionMt1=Last_TesnionMt1+0.07333*ErreurMt1-0.06869* Last_ErreurMt1;
	   Last_TesnionMt1=TensionMt1;
	   Last_ErreurMt1=ErreurMt1;
	   uint8_t CommandeMT1=((TensionMt1 / tensionMax) * PWM_PERIOD);
		if (CommandeMT1 > PWM_PERIOD)
		{
			CommandeMT1 = PWM_PERIOD;
		}

		if (CommandeMT1 <0)
		{
			 CommandeMT1=0;
		}
        TIM2->CCR1=CommandeMT1;
        HAL_Delay(DEL);
}
void Regulation_Mt6( float vitessem6,float  vitessem1,float vf,float tensionMax)
{
		float ErreurMt6=vf-vitessem6;
		TensionMt6=Last_TesnionMt6+0.07333*ErreurMt6-0.06869*Last_ErreurMt6; //commande
		Last_TesnionMt6=TensionMt6;
		Last_ErreurMt6=ErreurMt6;

		uint8_t CommandeMt6=((TensionMt6 / tensionMax) * PWM_PERIOD);

		if (CommandeMt6 > PWM_PERIOD)
		{
			CommandeMt6 = PWM_PERIOD;
		}

		if (CommandeMt6 <0)
		{
			CommandeMt6 = 0;
		}

		TIM3->CCR2=CommandeMt6;
		HAL_Delay(DEL);
		 //vitessem2-vitessem1;//erreur de synchronisation



}

void Regulation_Mt2( float vitessem2, float  vitessem5,float vf,float tensionMax)

{
		float ErreurMt2=vf-2*vitessem2+vitessem5;
		TensionMt2=Last_TesnionMt2+0.07333*ErreurMt2-0.06869* Last_ErreurMt2; //commande

		Last_TesnionMt2=TensionMt2;
		Last_ErreurMt2=ErreurMt2;

		uint8_t CommandeMt2=((TensionMt2 / tensionMax) * PWM_PERIOD);

		if (CommandeMt2 > PWM_PERIOD)
		{
			CommandeMt2 = PWM_PERIOD;
		}

		if (CommandeMt2 <0)
		{
			CommandeMt2 = 0;
		}

		TIM4->CCR2=CommandeMt2;
		HAL_Delay(DEL);
}
void Regulation_Mt5( float vitessem5,float  vitessem2,float vf,float tensionMax)

{

	  	float ErreurMt5=vf-2*vitessem5+vitessem2;
	  	TensionMt5=Last_TesnionMt5+0.07333*ErreurMt5-0.06869*Last_ErreurMt5; //commande
	  	Last_TesnionMt5=TensionMt5;
	  	Last_ErreurMt5=ErreurMt5;

	  	uint8_t CommandeMt5=((TensionMt5 / tensionMax) * PWM_PERIOD);

	  	if (CommandeMt5 > PWM_PERIOD)
	  	{
	  		CommandeMt5 = PWM_PERIOD;
	  	}

	  	if (CommandeMt5 <0)
	  	{
	  		CommandeMt5 = 0;
	  	}

	  	TIM3->CCR1=CommandeMt5;
	  	HAL_Delay(DEL);
}


void Regulation_Mt3( float vitessem3, float  vitessem4,float vf,float tensionMax)

{

		float ErreurMt3=vf-2*vitessem3+vitessem4;
	    TensionMt3=Last_TesnionMt3+0.07333*ErreurMt3-0.06869* Last_ErreurMt3; //commande
		Last_TesnionMt3=TensionMt3;
		Last_ErreurMt3=ErreurMt3;

		uint8_t CommandeMt3=((TensionMt3 / tensionMax) * PWM_PERIOD);

		if (CommandeMt3 > PWM_PERIOD)
		{
			CommandeMt3 = PWM_PERIOD;
		}

		if (CommandeMt3 <0)
		{
			CommandeMt3 = 0;
		}
	/*if(flag_deffaillanceM3_4>50){

		CommandeMt3=0;
	}*/
		TIM2->CCR3=CommandeMt3;
		HAL_Delay(DEL);


}
void Regulation_Mt4( float vitessem4,float  vitessem3,float vf,float tensionMax)

{

		float ErreurMt4=vf-2*vitessem4+vitessem3;
		TensionMt4=Last_TesnionMt4+0.07333*ErreurMt4-0.06869*Last_ErreurMt4; //commande
		Last_TesnionMt4=TensionMt4;
		Last_ErreurMt4=ErreurMt4;

		uint8_t CommandeMt4=((TensionMt4 / tensionMax) * PWM_PERIOD);

		if (CommandeMt4 > PWM_PERIOD)
		{
			CommandeMt4 = PWM_PERIOD;
		}

		if (CommandeMt4 <0)
		{
			CommandeMt4 = 0;
		}
		/*if(flag_deffaillanceM3_4>50){

			CommandeMt4=0;
		}*/
		TIM2->CCR4=CommandeMt4;
		HAL_Delay(DEL);
}







