/*
 * asservissement.c
 *
 *  Created on: Apr 24, 2023
 *      Author: m-ali.khlifi-ext
 */

#include "asservissement.h"
#include "main.h"
#include"stdio.h"
#include"gpio.h"
#include"stdlib.h"

#define PWM_PERIOD  100
// Déclarer des pointeurs pour stocker les valeurs dynamiquement
float *ErreurSynchronisationM1_M2;
float *TensionMt1;
float Last_TesnionMt1;
float Last_ErreurMt1;

float *TensionMt2;
float Last_TesnionMt2;
float Last_ErreurMt2;

float *ErreurSynchronisationM3_M4;
float *TensionMt3;
float Last_TesnionMt3;
float Last_ErreurMt3;

float *TensionMt4;
float Last_TesnionMt4;
float Last_ErreurMt4;

float *ErreurSynchronisationM5_M6;
float *TensionMt5;
float Last_TesnionMt5;
float Last_ErreurMt5;

float *TensionMt6;
float Last_TesnionMt6;
float Last_ErreurMt6;
extern uint8_t tens;
extern float speedMotor4;
float v4=0;
void Initialization()
{
    // Allouer de la mémoire dynamique pour les variables
    ErreurSynchronisationM1_M2 = (float *)malloc(sizeof(float));
    TensionMt1 = (float *)malloc(sizeof(float));


    TensionMt2 = (float *)malloc(sizeof(float));


        ErreurSynchronisationM3_M4 = (float *)malloc(sizeof(float));
        TensionMt3 = (float *)malloc(sizeof(float));

        TensionMt4 = (float *)malloc(sizeof(float));



        ErreurSynchronisationM5_M6 = (float *)malloc(sizeof(float));
        TensionMt5 = (float *)malloc(sizeof(float));


        TensionMt6 = (float *)malloc(sizeof(float));

}

void Cleanup()
{
    // Libérer la mémoire allouée dynamiquement
    free(ErreurSynchronisationM1_M2);
    free(TensionMt1);


    free(TensionMt2);

    free(ErreurSynchronisationM3_M4);
       free(TensionMt3);

       free(TensionMt4);


       free(ErreurSynchronisationM5_M6);
              free(TensionMt5);

              free(TensionMt6);

   }


void Regulation_Mt1( float vitessem1,float  vitessem2, float vitesseRef,float tensionMax)//reguler vitesse1 %vitesse reference et synchroniser avec vitesse2
{
	   float ErreurMt1=vitesseRef-2*vitessem1+ vitessem2;
       *TensionMt1=Last_TesnionMt1+0.06391*ErreurMt1-0.01931* Last_ErreurMt1; //commande

       //up1=P*u1p1+0.1*ep1-0.01*e1p1;
	   Last_TesnionMt1=*TensionMt1;
	   Last_ErreurMt1=ErreurMt1;
	   uint8_t CommandeMT1=((*TensionMt1 / tensionMax) * PWM_PERIOD);
		if (CommandeMT1 > PWM_PERIOD)
		{
			CommandeMT1 = PWM_PERIOD;
		}

		if (CommandeMT1 <0)
		{
			 CommandeMT1=0;
		}

		TIM1->CCR1=CommandeMT1;
HAL_Delay(6);

		// Cleanup();

}
void Regulation_Mt2( float vitessem2, float  vitessem1,float vf,float tensionMax)

{

	float ErreurMt2=vf-2*vitessem2+vitessem1;
	*TensionMt2=Last_TesnionMt2+0.0639*ErreurMt2-0.01931* Last_ErreurMt2; //commande

	Last_TesnionMt2=*TensionMt2;
	Last_ErreurMt2=ErreurMt2;

	uint8_t CommandeMt2=((*TensionMt2 / tensionMax) * PWM_PERIOD);

	if (CommandeMt2 > PWM_PERIOD)
	{
		CommandeMt2 = PWM_PERIOD;
	}

	if (CommandeMt2 <0)
	{
		CommandeMt2 = 0;
	}

	TIM1->CCR2=CommandeMt2;
	HAL_Delay(6);


	// Cleanup();
}

void Regulation_Mt3( float vitessem3, float  vitessem4,float vf,float tensionMax)

{
	float ErreurMt3=vf-2*vitessem3+vitessem4;
    *TensionMt3=Last_TesnionMt3+0.0639*ErreurMt3-0.01931* Last_ErreurMt3; //commande
	Last_TesnionMt3=*TensionMt3;
	Last_ErreurMt3=ErreurMt3;

	uint8_t CommandeMt3=((*TensionMt3 / tensionMax) * PWM_PERIOD);

	if (CommandeMt3 > PWM_PERIOD)
	{
		CommandeMt3 = PWM_PERIOD;
	}

	if (CommandeMt3 <0)
	{
		CommandeMt3 = 0;
	}

	TIM1->CCR3=CommandeMt3;
	HAL_Delay(6);

	 //Cleanup();


}
void Regulation_Mt4( float vitessem4,float  vitessem3,float vf,float tensionMax)

{

	float ErreurMt4=vf-2*vitessem4+vitessem3;

	*TensionMt4=Last_TesnionMt4+0.0639*ErreurMt4-0.01931*Last_ErreurMt4; //commande
	Last_TesnionMt4=*TensionMt4;
	Last_ErreurMt4=ErreurMt4;

	uint8_t CommandeMt4=((*TensionMt4 / tensionMax) * PWM_PERIOD);

	if (CommandeMt4 > PWM_PERIOD)
	{
		CommandeMt4 = PWM_PERIOD;
	}

	if (CommandeMt4 <0)
	{
		CommandeMt4 = 0;
	}

	TIM3->CCR1=CommandeMt4;
	HAL_Delay(20);
v4=speedMotor4*60;
	 //Cleanup();


}


void Regulation_Mt5( float vitessem5,float  vitessem6,float vf,float tensionMax)

{




	float ErreurMt5=vf-2*vitessem5+vitessem6;


	*TensionMt5=Last_TesnionMt5+0.00639*ErreurMt5-0.001931*Last_ErreurMt5; //commande
	Last_TesnionMt5=*TensionMt5;
	Last_ErreurMt5=ErreurMt5;

	uint8_t CommandeMt5=((*TensionMt5 / tensionMax) * PWM_PERIOD);

	if (CommandeMt5 > PWM_PERIOD)
	{
		CommandeMt5 = PWM_PERIOD;
	}

	if (CommandeMt5 <0)
	{
		CommandeMt5 = 0;
	}

	TIM3->CCR2=CommandeMt5;

	HAL_Delay(2);

	Cleanup();

}

void Regulation_Mt6( float vitessem6,float  vitessem5,float vf,float tensionMax)

{




		float ErreurMt6=vf-2*vitessem6+vitessem5;

	*TensionMt6=Last_TesnionMt6+0.00639*ErreurMt6-0.001931*Last_ErreurMt6; //commande
	Last_TesnionMt6=*TensionMt6;
	Last_ErreurMt6=ErreurMt6;

	uint8_t CommandeMt6=((*TensionMt6 / tensionMax) * PWM_PERIOD);

	if (CommandeMt6 > PWM_PERIOD)
	{
		CommandeMt6 = PWM_PERIOD;
	}

	if (CommandeMt6 <0)
	{
		CommandeMt6 = 0;
	}

	TIM3->CCR3=CommandeMt6;
	HAL_Delay(2);


	Cleanup();


}


