/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "asservissement.h"
#include "interruption.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define frequencyM1     1000/(periodMotor1)    // FREQUENCE DU L ENCODEUR 1
#define frequencyM2     1000/(periodMotor2)    // FREQUENCE DU L ENCODEUR 2
#define frequencyM3     1000/(periodMotor3)    // FREQUENCE DU L ENCODEUR 3
#define frequencyM4     1000/(periodMotor4)    // FREQUENCE DU L ENCODEUR 4
#define frequencyM5     1000/(periodMotor5)    // FREQUENCE DU L ENCODEUR 5
#define frequencyM6     1000/(periodMotor6)    // FREQUENCE DU L ENCODEUR 6

#define Vmin     15   // FREQUENCE DU L ENCODEUR 6
#define Vmax     45  // FREQUENCE DU L ENCODEUR 6
#define Vx     19 // FREQUENCE DU L ENCODEUR 6

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int speedMotor1=0;
int speedMotor2=0;
int speedMotor3=0;
int speedMotor4=0;
int speedMotor5=0;
int speedMotor6=0;
float vitesseRef1 =25;            // VITESSE DE REFERNCE POUR L ASSERVISSEMENT 90
float vitesseRef3 =25;
float vitesseRef2 =25;
int periodMotor1=0;
uint16_t periodMotor2=0;
uint16_t periodMotor3=0;
uint16_t periodMotor4=0;
uint16_t periodMotor5=0;
uint16_t periodMotor6=0;
volatile float Is_First_Captured1=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 1 EST DETECTE
volatile float Is_First_Captured2=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 2 EST DETECTE
volatile float Is_First_Captured3=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 3 EST DETECTE
volatile float Is_First_Captured4=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 4 EST DETECTE
volatile float Is_First_Captured5=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 5 EST DETECTE
volatile float Is_First_Captured6=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 6 EST DETECTE
volatile int IC1_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 1
volatile int IC2_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 2
volatile int IC3_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 3
volatile int IC4_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 4
volatile int IC5_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 5
volatile int IC6_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 6
volatile int CountM1=0;      // NOMBRE D IMPULSION ENCODEUR 1
volatile int CountM2=0;      // NOMBRE D IMPULSION ENCODEUR 2
volatile int CountM3=0;      // NOMBRE D IMPULSION ENCODEUR 3
volatile int CountM4=0;      // NOMBRE D IMPULSION ENCODEUR 4
volatile int CountM5=0;      // NOMBRE D IMPULSION ENCODEUR 5
volatile int CountM6=0;      // NOMBRE D IMPULSION ENCODEUR 6
double pos1;
double pos2;
double pos3;
 uint8_t Msgsent_ToST2[1]={0x1F};//1 identificateur/ F start mise à zero
 uint8_t senddataPOS_encour[1]={0x11};//1 identificateur/ 1  mise à zero en cours
 uint8_t senddatahold[1]={0xF0};//F tout les uc/ 0 terminer la  mise à zero

 uint8_t MsgrecuST2[1];//RX UART:: courantR1  COURANTR2 COURANTR3 /R4  DESC  COURANTMEULE  /COUNTMR1 MR2...MR4
uint32_t BATT;       // TABLEAU POUR STOCKER VALEUR DE TENSION BATT
double y=-580;
double x=-30;


volatile float VBATT=20;
volatile float COURANTV1;
volatile float COURANTV2;
volatile float COURANTV3;
volatile float COURANTV4;
volatile float COURANTV5;
volatile float COURANTV6;
uint8_t  courantR1;
uint8_t  courantR2;
uint8_t  courantR3;
uint8_t  courantR4;
uint8_t  courantDESC ;
uint8_t courantMeule;
uint8_t CountMR1;
uint8_t CountMR2;
uint8_t CountMR3;
uint8_t CountMR4;
uint8_t CountDESC;
uint16_t buffer1[3];
uint16_t buffer2[3];
uint8_t Start;//bouton start cycle
float resultats;
float t1;
float t2;
float t3;
const float PI=3.141593;

double poszero1;
double poszero2;
double poszero3;
int zero=0;
int mise_zero_alpha0=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void roundpulse(double *C1,double *C2,double *C3);

void ConvertMM_topulse(double *C1,double *C2,double *C3);

void determinerVecteurTEMPS( double *pos11,double *pos22,double *pos33 );
void convert_Frompolar_Tocourse(double x, double y, double alpha);
void moveTo( double x,double y,double alpha );
void Start_mise_a_zero();
void senddataholdTo_st2();
void Mise_a_zero_encour();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)

{
	  if(htim->Instance==TIM8)
	  {
		  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)// MOTEUR 1

		  	{
			   Interruption_1();
             // CountM1++;


				if (Is_First_Captured1 == 0)
					{

					  IC1_Val1=HAL_GetTick();
					  Is_First_Captured1++;

					}
		  		else if (Is_First_Captured1 == 1)
					{
					  periodMotor1 = HAL_GetTick()-IC1_Val1;//periode1
					  if(periodMotor1>16)
					  {
					    speedMotor1 = frequencyM1;


					  }
					  Is_First_Captured1 = 0;

					  }

		  	}
		  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)// MOTEUR 2

		 		  	            {
		 						 Initerruption_2();
		 		            	 //CountM2+=1;

		 						  if (Is_First_Captured2 == 0)
		 							{
		 								IC2_Val1=HAL_GetTick();
		 								Is_First_Captured2++;
		 							}
		 							else if (Is_First_Captured2 == 1)
		 							{
		 								periodMotor2 = HAL_GetTick()-IC2_Val1;//periode1
		 								if(periodMotor2>16)
		 								{
		 								speedMotor2 = frequencyM2;
		 								}

		 								Is_First_Captured2 = 0;

		 							}


		 						  }
	  }





	  if(htim->Instance==TIM1)

	  {

            if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)	//MOTEUR3

				{
	    Interruption_3();
  	 //CountM3++;

					if (Is_First_Captured3 == 0)
						{
							IC3_Val1=HAL_GetTick();
							Is_First_Captured3++;
						}
					else if (Is_First_Captured3 == 1)
						{
							periodMotor3 = HAL_GetTick()-IC3_Val1;//periode1
							if(periodMotor3>16)
							{
							  speedMotor3 = frequencyM3;
							}
							Is_First_Captured3 = 0;

						}

				}



	  		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)//MOTEUR4
	  			  {
	  			    Interruption_4();
	  			//CountM4++;

					   if (Is_First_Captured4 == 0)
						   {
								IC4_Val1=HAL_GetTick();
								//timestamp1C1 = HAL_GetTick();
								Is_First_Captured4++;
						   }
						else if (Is_First_Captured4== 1)
							{
								periodMotor4 = HAL_GetTick()-IC4_Val1;//periode1periode1*0.5 both edge
							    if(periodMotor4>16)
							    {
								  speedMotor4 = frequencyM4;
								}
								Is_First_Captured4 = 0;

							}

					}

	  		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)//MOTEUR5
				{
				     Interruption_5();
	  			 //CountM5++;

					 if (Is_First_Captured5 == 0)
						{
							IC5_Val1=HAL_GetTick();
							//timestamp1C1 = HAL_GetTick();
							Is_First_Captured5++;
						}
					 else if (Is_First_Captured5== 1)
						{
							periodMotor5 = HAL_GetTick()-IC5_Val1;//periode1
							if(periodMotor5>16)
							{
							  speedMotor5 = frequencyM5;
							}
							Is_First_Captured5 = 0;

						}

				}
	  		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)//MOTEUR6
				{
					Interruption_6();
	  			//  CountM6++;

					if (Is_First_Captured6 == 0)
					{
						IC6_Val1=HAL_GetTick();
						//timestamp1C1 = HAL_GetTick();
						Is_First_Captured6++;
					}
					else if (Is_First_Captured6== 1)
						{
							periodMotor6 = HAL_GetTick()-IC6_Val1;//periode1periode1*0.5 both edge
						    if(periodMotor6>16)
						    {
							  speedMotor6 =frequencyM6;
						    }
							Is_First_Captured6 = 0;

						}

	  			 }

	  	}

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

	  /*  if (hadc->Instance == ADC1)
	    {
				COURANTV1=buffer1[0];
				COURANTV2=buffer1[1];
				COURANTV3=buffer1[2];

	    }*/
	     if (hadc->Instance == ADC2)
	    {

	 	     VBATT=(BATT/ 4095.00)*21;//tension de la batterie

	    }
	 /* if (hadc->Instance == ADC3)
	        {
				COURANTV4=buffer2[0];
				COURANTV5=buffer2[1];
				COURANTV6=buffer2[2];

	        }*/





}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
  {
	HAL_UART_Receive_IT(&huart1,MsgrecuST2, 1);//sizeof(buffer));// CR1/CR2/CR3/CR4/CRDES/CRMEULE/CountMR1...CountMR4

  }

void Start_mise_a_zero()
  {

   HAL_UART_Transmit_IT(&huart1, Msgsent_ToST2, 1);// ENVOYER 011=3
HAL_Delay(100);

  }
void Mise_a_zero_encour()
  {

   HAL_UART_Transmit_IT(&huart1, senddataPOS_encour, 1);
   HAL_Delay(100);


  }
void senddataholdTo_st2()

  {

   HAL_UART_Transmit_IT(&huart1, senddatahold, 1);
   HAL_Delay(100);


  }

void check_batterie(){
	if(VBATT>17.00){


		HAL_GPIO_WritePin(GPIOB, Led_Level_BATT_Pin, GPIO_PIN_SET);
	}
	else if(VBATT<17.00){

		HAL_GPIO_TogglePin(GPIOB, Led_Level_BATT_Pin);
		HAL_Delay(100);
	}
}







void convert_Frompolar_Tocourse(double x, double y, double alpha){

alpha=PI*alpha/180;// angle radian
pos1=sqrt(pow(x+180*sin(alpha)-50*cos(alpha),2)+pow(y+180*cos(alpha)+50*sin(alpha),2))-356;// EQUATION COURSE1
pos2=sqrt(pow(x+180*sin(alpha)-50*cos(alpha)+100,2)+pow(y+180*cos(alpha)+50*sin(alpha),2))-356;//EQUATION COURSE 2
pos3=sqrt(pow(x+180*sin(alpha)+50*cos(alpha)-80,2)+pow(y+180*cos(alpha)-50*sin(alpha),2))-356;// EQUATION COURSE3
if(pos1<0){pos1=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course
if(pos2<0){pos2=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course
if(pos3<0){pos3=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course

}
void roundpulse(double *C1,double *C2,double *C3)
{
	*C1=round(*C1);
	*C2=round(*C2);
	*C3=round(*C3);
}
void ConvertMM_topulse(double *C1,double *C2,double *C3)
{
	*C1=(*C1)*6.41;
	*C2=(*C2)*6.41;
	*C3=(*C3)*6.41;

}
void determinerVecteurTEMPS( double *pos11,double *pos22,double *pos33 )
  {

		t1=*pos11/vitesseRef1;
		t2=*pos22/vitesseRef2;
		t3=*pos33/vitesseRef3;
		resultats= (t2+t3+t1)/3;
   }
void moveTo( double x,double y,double alpha ){

vitesseRef1=30;
vitesseRef2=30;
vitesseRef3=30;
poszero1=pos1;
poszero2=pos2;
poszero3=pos3;

convert_Frompolar_Tocourse(x, y, alpha);//retourner pos1 POS2 POS3 en mm
//ConvertMM_topulse(&pos1, &pos2, &pos3);
  // roundpulse(&pos1, &pos2, &pos3);

if ((pos1 == 0 && pos3 == 0) && pos2 == 0) {
    vitesseRef1 = ceil(poszero1 / resultats);
    vitesseRef2 = ceil(poszero2 / resultats);
    vitesseRef3 = ceil(poszero3 / resultats);
} else {
    ConvertMM_topulse(&pos1, &pos2, &pos3);
    roundpulse(&pos1, &pos2, &pos3);
    determinerVecteurTEMPS(&pos1, &pos2, &pos3);

    vitesseRef1 = ceil(pos1 / resultats);//
    vitesseRef2 = ceil(pos2 / resultats);
    vitesseRef3 = ceil(pos3 / resultats);
}

vitesseRef1 = (vitesseRef1 > Vmax) ? Vmax : (vitesseRef1 < Vmin) ? Vmin : vitesseRef1;
vitesseRef2 = (vitesseRef2 > Vmax) ? Vmax : (vitesseRef2 < Vmin) ? Vmin : vitesseRef2;
vitesseRef3 = (vitesseRef3 > Vmax) ? Vmax : (vitesseRef3 < Vmin) ? Vmin : vitesseRef3;



////////////////////////////////////////

while ( ((pos1>CountM2)||(pos1>CountM5)||(pos1-CountM2<0 )||(pos1-CountM5<0 ) ||
		(pos2>CountM1)||(pos2>CountM6)||(pos2-CountM1<0 ) ||(pos2-CountM6<0 )||
		(pos3>CountM3)||(pos3>CountM4)||(pos3-CountM3<0 ) ||(pos3-CountM4<0 )))
{
	///{1 ET 6}  {2 ET 5}   {3  ET 4} sont synchroniser deux a deux
	 //////////////////////////////////////////////////////////MOTEUR1



    if (pos2 - CountM1 > 0) {
        HAL_GPIO_WritePin(GPIOC, VINB1_Pin, GPIO_PIN_RESET); // Moving forward
         Regulation_Mt1(speedMotor1, speedMotor6, vitesseRef2, VBATT)   ;
        //TIM2->CCR1 = 40; // Stop for any other condition

    } else if ((pos2 - CountM1) < 0 ) {
        HAL_GPIO_WritePin(GPIOC, VINB1_Pin, GPIO_PIN_SET); // Moving backward
        Regulation_Mt1(speedMotor1, speedMotor6, vitesseRef2, VBATT)   ;
        //TIM2->CCR1 = 40;
    } else {
        TIM2->CCR1 = 0; // Stop for any other condition
    }

    ////////////////////////////////////////////////////////////////////MT6

    	    if (pos2 - CountM6 > 0) {
    	    	HAL_GPIO_WritePin(GPIOC,  VINB6_Pin, GPIO_PIN_RESET);
    			Regulation_Mt6(speedMotor6, speedMotor1, vitesseRef2, VBATT);

    	    	 //TIM3->CCR2=40;
    	    }
    	    else if ((pos2 - CountM6 )< 0 )
    	    {

    	      HAL_GPIO_WritePin(GPIOC,  VINB6_Pin, GPIO_PIN_SET);
    		  Regulation_Mt6(speedMotor6, speedMotor1, vitesseRef2, VBATT);
    	      //TIM3->CCR2=40;

    	    }

    	    else
    	    {
    		  	TIM3->CCR2=0;

    	    }

	  ///////////////////////////////////////////////////MOTEUR2


		if  (pos1- CountM2>0 )//>=0.4
		   {

			HAL_GPIO_WritePin(GPIOC,  VINB2_Pin, GPIO_PIN_RESET);
		    Regulation_Mt2(speedMotor2, speedMotor5,vitesseRef1, VBATT);

			 //TIM4->CCR2=40;

		   }else if (( pos1 - CountM2   )<0  )//<=-0.5
				{
				   HAL_GPIO_WritePin(GPIOC,  VINB2_Pin, GPIO_PIN_SET);
				   Regulation_Mt2(speedMotor2, speedMotor5,vitesseRef1, VBATT);
				  // TIM4->CCR2=40;
			    }

		   else
			    {
			   TIM4->CCR2=0;

			    }

		///////////////////////////////////////////////////MOTEUR5


		if (pos1 - CountM5 > 0) {
			   HAL_GPIO_WritePin(GPIOC,  VINB5_Pin, GPIO_PIN_RESET);
			  Regulation_Mt5(speedMotor5, speedMotor2, vitesseRef1, VBATT);

			   //TIM3->CCR1=40;
		    } else if ((pos1 - CountM5) < 0 ) {

				  HAL_GPIO_WritePin(GPIOC,  VINB5_Pin, GPIO_PIN_SET);
				  Regulation_Mt5(speedMotor5, speedMotor2, vitesseRef1, VBATT);
				 // TIM3->CCR1=40;

		    }


		    else {
			  	TIM3->CCR1=0;


		    }

	///////////////////////////////////////////////////////////MOTEUR3


			if (pos3 - CountM3 > 0)
			  {
				HAL_GPIO_WritePin(GPIOC,  VINB3_Pin, GPIO_PIN_RESET);
				Regulation_Mt3(  speedMotor3,   speedMotor4, vitesseRef3, VBATT);
				 //TIM2->CCR3=40;
			   } else if ((pos3 - CountM3 )< 0 )
					   {
				  HAL_GPIO_WritePin(GPIOC,  VINB3_Pin, GPIO_PIN_SET);

				  Regulation_Mt3(  speedMotor3, speedMotor4, vitesseRef3, VBATT);

			   }

			   else {
				   TIM2->CCR3=0;


			   }
/////////////////////////////////////////////////////////////////////////////////MT4


		   if (pos3 - CountM4 > 0)
		   {
			 HAL_GPIO_WritePin(GPIOC,  VINB4_Pin, GPIO_PIN_RESET);

			  Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef3, VBATT);

			 //TIM2->CCR4=40;
		   }
		   else if ((pos3 - CountM4 )< 0 )
		   {
			HAL_GPIO_WritePin(GPIOC,  VINB4_Pin, GPIO_PIN_SET);

			  Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef3, VBATT);

			  // TIM2->CCR4=40;
		   }


		   else
		   {
			   TIM2->CCR4=0;


		   }



}
////////////////////////////////////////////////////////////////////////////
                  if  (( pos2  -CountM1  )==0 )
					   {
       			   TIM2->CCR1=0;

					   }
				 if  (( pos1  -CountM2  )==0 )
					   {
					   TIM4->CCR2=0;

					   }

	 			 if  (( pos3  -CountM3  )==0 )
				     {
	 				   TIM2->CCR3=0;

				     }
				 if  (( pos3  -CountM4 )==0 )
				     {
					   TIM2->CCR4=0;

					 }
				 if  (( pos1  -CountM5  )==0 )
				     {
					  	TIM3->CCR1=0;

					 }
				if  (( pos2 -CountM6  )==0 )
					 {
				  	TIM3->CCR2=0;

					 }

}

void moveTozero( double x,double y,double alpha ){

vitesseRef1=25;
vitesseRef2=25;
vitesseRef3=25;
poszero1=pos1;
poszero2=pos2;
poszero3=pos3;

convert_Frompolar_Tocourse(x, y, alpha);//retourner pos1 POS2 POS3 en mm
//ConvertMM_topulse(&pos1, &pos2, &pos3);
  // roundpulse(&pos1, &pos2, &pos3);

if ((pos1 == 0 && pos3 == 0) && pos2 == 0) {
    vitesseRef1 = ceil(poszero1 / resultats);
    vitesseRef2 = ceil(poszero2 / resultats);
    vitesseRef3 = ceil(poszero3 / resultats);
} else {
    ConvertMM_topulse(&pos1, &pos2, &pos3);
    roundpulse(&pos1, &pos2, &pos3);
    determinerVecteurTEMPS(&pos1, &pos2, &pos3);

    vitesseRef1 = ceil(pos1 / resultats);//
    vitesseRef2 = ceil(pos2 / resultats);
    vitesseRef3 = ceil(pos3 / resultats);
}

vitesseRef1 = (vitesseRef1 > Vx) ? Vx : (vitesseRef1 < Vmin) ? Vmin : vitesseRef1;
vitesseRef2 = (vitesseRef2 > Vx) ? Vx : (vitesseRef2 < Vmin) ? Vmin : vitesseRef2;
vitesseRef3 = (vitesseRef3 > Vx) ? Vx : (vitesseRef3 < Vmin) ? Vmin : vitesseRef3;



////////////////////////////////////////

while ( ((pos1>CountM2)||(pos1>CountM5)||(pos1-CountM2<0 )||(pos1-CountM5<0 ) ||
		(pos2>CountM1)||(pos2>CountM6)||(pos2-CountM1<0 ) ||(pos2-CountM6<0 )||
		(pos3>CountM3)||(pos3>CountM4)||(pos3-CountM3<0 ) ||(pos3-CountM4<0 ))&& MsgrecuST2[0]==5)
{
	///{1 ET 6}  {2 ET 5}   {3  ET 4} sont synchroniser deux a deux
	 //////////////////////////////////////////////////////////MOTEUR1



    if (pos2 - CountM1 > 0 && MsgrecuST2[0]==5) {
        HAL_GPIO_WritePin(GPIOC, VINB1_Pin, GPIO_PIN_RESET); // Moving forward
         Regulation_Mt1(speedMotor1, speedMotor6, vitesseRef2, VBATT)   ;
        //TIM2->CCR1 = 40; // Stop for any other condition

    } else if ((pos2 - CountM1) < 0 && MsgrecuST2[0]==5 ) {
        HAL_GPIO_WritePin(GPIOC, VINB1_Pin, GPIO_PIN_SET); // Moving backward
        Regulation_Mt1(speedMotor1, speedMotor6, vitesseRef2, VBATT)   ;
        //TIM2->CCR1 = 40;
    } else {
        TIM2->CCR1 = 0; // Stop for any other condition
    }

    ////////////////////////////////////////////////////////////////////MT6

    	    if (pos2 - CountM6 > 0 && MsgrecuST2[0]==5) {
    	    	HAL_GPIO_WritePin(GPIOC,  VINB6_Pin, GPIO_PIN_RESET);
    			Regulation_Mt6(speedMotor6, speedMotor1, vitesseRef2, VBATT);

    	    	 //TIM3->CCR2=40;
    	    }
    	    else if ((pos2 - CountM6 )< 0 && MsgrecuST2[0]==5)
    	    {

    	      HAL_GPIO_WritePin(GPIOC,  VINB6_Pin, GPIO_PIN_SET);
    		  Regulation_Mt6(speedMotor6, speedMotor1, vitesseRef2, VBATT);
    	      //TIM3->CCR2=40;

    	    }

    	    else
    	    {
    		  	TIM3->CCR2=0;

    	    }

	  ///////////////////////////////////////////////////MOTEUR2


		if  (pos1- CountM2>0 && MsgrecuST2[0]==5 )//>=0.4
		   {

			HAL_GPIO_WritePin(GPIOC,  VINB2_Pin, GPIO_PIN_RESET);
		    Regulation_Mt2(speedMotor2, speedMotor5,vitesseRef1, VBATT);

			 //TIM2->CCR2=40;

		   }else if (( pos1 - CountM2   )<0 && MsgrecuST2[0]==5 )//<=-0.5
				{
				   HAL_GPIO_WritePin(GPIOC,  VINB2_Pin, GPIO_PIN_SET);
				   Regulation_Mt2(speedMotor2, speedMotor5,vitesseRef1, VBATT);
				  // TIM2->CCR2=40;
			    }

		   else
			    {
			   TIM4->CCR2=0;

			    }

		///////////////////////////////////////////////////MOTEUR5


		if (pos1 - CountM5 > 0 && MsgrecuST2[0]==5) {
			   HAL_GPIO_WritePin(GPIOC,  VINB5_Pin, GPIO_PIN_RESET);
			  Regulation_Mt5(speedMotor5, speedMotor2, vitesseRef1, VBATT);

			   //TIM3->CCR1=40;
		    } else if ((pos1 - CountM5) < 0 && MsgrecuST2[0]==5) {

				  HAL_GPIO_WritePin(GPIOC,  VINB5_Pin, GPIO_PIN_SET);
				  Regulation_Mt5(speedMotor5, speedMotor2, vitesseRef1, VBATT);
				 // TIM3->CCR1=40;

		    }


		    else {
			  	TIM3->CCR1=0;


		    }

	///////////////////////////////////////////////////////////MOTEUR3


			if (pos3 - CountM3 > 0 && MsgrecuST2[0]==5)
			  {
				HAL_GPIO_WritePin(GPIOC,  VINB3_Pin, GPIO_PIN_RESET);
				Regulation_Mt3(  speedMotor3,   speedMotor4, vitesseRef3, VBATT);
				 //TIM2->CCR3=40;
			   } else if ((pos3 - CountM3 )< 0 && MsgrecuST2[0]==5 )
					   {
				  HAL_GPIO_WritePin(GPIOC,  VINB3_Pin, GPIO_PIN_SET);

				  Regulation_Mt3(  speedMotor3, speedMotor4, vitesseRef3, VBATT);

			   }

			   else {
				   TIM2->CCR3=0;


			   }
/////////////////////////////////////////////////////////////////////////////////MT4


		   if (pos3 - CountM4 > 0 && MsgrecuST2[0]==5)
		   {
			 HAL_GPIO_WritePin(GPIOC,  VINB4_Pin, GPIO_PIN_RESET);

			  Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef3, VBATT);

			 //TIM2->CCR4=40;
		   }
		   else if ((pos3 - CountM4 )< 0 && MsgrecuST2[0]==5 )
		   {
			HAL_GPIO_WritePin(GPIOC,  VINB4_Pin, GPIO_PIN_SET);

			  Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef3, VBATT);

			  // TIM2->CCR4=40;
		   }


		   else
		   {
			   TIM2->CCR4=0;


		   }



}
////////////////////////////////////////////////////////////////////////////
                  if  (( pos2  -CountM1  )==0 || MsgrecuST2[0]==4)
					   {
       			   TIM2->CCR1=0;

					   }
				 if  (( pos1  -CountM2  )==0 || MsgrecuST2[0]==4 )
					   {
					   TIM4->CCR2=0;

					   }

	 			 if  (( pos3  -CountM3  )==0 || MsgrecuST2[0]==4)
				     {
	 				   TIM2->CCR3=0;

				     }
				 if  (( pos3  -CountM4 )==0 || MsgrecuST2[0]==4)
				     {
					   TIM2->CCR4=0;

					 }
				 if  (( pos1  -CountM5  )==0 || MsgrecuST2[0]==4 )
				     {
					  	TIM3->CCR1=0;

					 }
				if  (( pos2 -CountM6  )==0 || MsgrecuST2[0]==4)
					 {
				  	TIM3->CCR2=0;

					 }

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM8_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_ADC2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

	HAL_UART_Receive_IT(&huart1,MsgrecuST2, 1);//sizeof(buffer));
	//moteur1
	HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);//PC6 START INTERRUPTION
	//moteur2
	HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);//PC7

	//moteur3
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);//PE9
	//moteur4
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);//PE11
	//moteur5
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);//PE13
	//moteur6
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);//PE14
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//MT5
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//MT6
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//MT1

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//MT2

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//MT3
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//MT4


	//HAL_ADC_Start_DMA(&hadc1,(uint32_t *)buffer1, 3);// V1 V2 V3
	//HAL_ADC_Start_DMA(&hadc2,&BATT, 1);
	//HAL_ADC_Start_DMA(&hadc3,(uint32_t *)buffer2, 3);// V4 V5 V6
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      moveTo(-70, -550, -30);



/*while(mise_zero_alpha0==0){
	   	 if(zero==0){

	   moveTo(0, y, 0);
	   Start_mise_a_zero();
	   	 }//send 3 to st2
	   if(MsgrecuST2[0]==0x21){

		   Mise_a_zero_encour();//SEND 1/ ENCOUR
	   	zero=1;

	   }

	   while(MsgrecuST2[0]==0x21){
	   moveTo(0, y, 0);
	    y=y-0.5;
//	    x=x-0.5;

   	    zero=1;
	   }


	   if(MsgrecuST2[0]==0xF0)
	   {

	   senddataholdTo_st2();//0XF0
	   //mise_zero_alpha0=1;
	   if(HAL_GPIO_ReadPin(GPIOB, START_Pin)==1){

	       moveTo(0, 0, 0);

	   }


	   }
}*/



  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */