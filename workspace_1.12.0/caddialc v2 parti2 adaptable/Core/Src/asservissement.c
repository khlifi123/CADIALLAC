/*
 * asservissement.c
 *
 *  Created on: Feb 27, 2024
 *      Author: m-ali.khlifi
 */
#include "main.h"

#include "time.h"
#define PWM_PERIOD  100
#define DEL 20

// Déclarer des pointeurs pour stocker les valeurs dynamiquement
float TensionMt1;
float Last_TesnionMt1;
float Last_ErreurMt1;


float TensionMt6;
float Last_TesnionMt6;
float Last_ErreurMt6;







void Regulation_Mt1( float vitessem1, float vf,float tensionMax)//reguler vitesse1 %vitesse reference et synchroniser avec vitesse2
{

	   float ErreurMt1=vf-vitessem1;
	   TensionMt1=Last_TesnionMt1+0.7333*ErreurMt1-0.6869* Last_ErreurMt1;
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
void Regulation_MtR2( float vitessem2,float vf,float tensionMax)
{
		float ErreurMt6 = vf-vitessem2;
		TensionMt6=Last_TesnionMt6+0.7333*ErreurMt6-0.6869*Last_ErreurMt6; //commande
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

		TIM2->CCR2=CommandeMt6;
		HAL_Delay(1);
		 //vitessem2-vitessem1;//erreur de synchronisation



}
