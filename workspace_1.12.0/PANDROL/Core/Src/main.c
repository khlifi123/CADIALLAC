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

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define frequencyM1     1000/(periodMotor1)    // FREQUENCE DU L ENCODEUR 1
#define frequencyM2     1000/(periodMotor2)    // FREQUENCE DU L ENCODEUR 2
#define frequencyM3     1000/(periodMotor3)    // FREQUENCE DU L ENCODEUR 3
#define frequencyM4     1000/(periodMotor4)    // FREQUENCE DU L ENCODEUR 4
#define frequencyM5     1000/(periodMotor5)    // FREQUENCE DU L ENCODEUR 5
#define frequencyM6     1000/(periodMotor6)    // FREQUENCE DU L ENCODEUR 6
#define   Vmax           30
#define   Vmin           17

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void moveTo( double pos1,double pos2,double pos3);                  // FONCTION POUR AVANCER ET RECULER LES VERINS
void roundpulse(double *C1,double *C2,double *C3);                // ROUND DES COURSES
void convert_Frompolar_Tocourse(double x, double y, double alpha);//COORDONNEE POLAIRE TO COURSE
void Commander_Moteuraxial();               // MOUVEMENT AXIAL DU MOTEUR SELON LES DEUX CAPTEUR
void ConvertMM_topulse(double *C1,double *C2,double *C3);
void determinerVecteurTEMPS( double *pos11,double *pos22,double *pos33 );
void zerodefine();
void Position_Zero(double pos3);
//definitions des vitesses exp speedMotor1-->vitesse du moteur 1
float speedMotor1=0;
float speedMotor2=0;
float speedMotor3=0;
float speedMotor4=0;
float speedMotor5=0;
float speedMotor6=0;
float vitesseRef1 =20  ;            // VITESSE DE REFERNCE POUR L ASSERVISSEMENT 90
float vitesseRef3 =25;
float vitesseRef2 =20;
//definitions des periodes entre deux fronts montant periodMotor1
uint16_t periodMotor1=0;
uint16_t periodMotor2=0;
uint16_t periodMotor3=0;
uint16_t periodMotor4=0;
uint16_t periodMotor5=0;
uint16_t periodMotor6=0;

/* USER CODE END 0 */
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

uint32_t readValue;
uint32_t temp;

int CountM1=0;      // NOMBRE D IMPULSION ENCODEUR 1
int CountM2=0;      // NOMBRE D IMPULSION ENCODEUR 2
int CountM3=0;      // NOMBRE D IMPULSION ENCODEUR 3
int CountM4=0;      // NOMBRE D IMPULSION ENCODEUR 4
int CountM5=0;      // NOMBRE D IMPULSION ENCODEUR 5
int CountM6=0;      // NOMBRE D IMPULSION ENCODEUR 6
int COUNTR1=0;
int COUNTR2=0;

char data,data1;
int flag=0;
char dta='k'; // A ENVOYER VER LE PC POUR CONNECTER A PRONTERFACE
const float PI=3.141593;
double pos1;
double pos2;
double pos3;
// Global variable to store the previous CountM1 value
float t1;
float t2;
float t3;
float resultats;
double poszero1;
double poszero2;
double poszero3;
char tab[16]={};
float c=3;
float current;
float sensitivity =0.066;
uint32_t moyenne = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	  if(htim->Instance==TIM2)
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
					  if(periodMotor1!=0)
					  {
					    speedMotor1 = frequencyM1;


					  }
					  Is_First_Captured1 = 0;

					}

		  	}if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)// ROULEAU1 PB3

		  	     {
		  		COUNTR1++;
                 }
		  	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)// ROULEAU2 PA2

     		    	{
                	 COUNTR2++;

                      }

	  }

		  if(htim->Instance==TIM8)
		 	 {
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
								if(periodMotor2!=0)
								{
								speedMotor2 = frequencyM2;
								}

								Is_First_Captured2 = 0;

							}


						  }

	                }



	  if(htim->Instance==TIM4)

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
							if(periodMotor3!=0)
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
							    if(periodMotor4!=0)
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
							if(periodMotor5!=0)
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
						    if(periodMotor6!=0)
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
	 if (hadc->Instance == ADC2)
	  {


		 //valeurACS712();
      //current=readValue *3.30/ 4095;
		 current = (( readValue*3.30/ 4095)-1.63)/0.066;
		  if(current < 0) current=-current;

		 //c =abs(rawVoltage - 1.63)/0.066;

	  }

}

void roundpulse(double *C1,double *C2,double *C3)
{
	*C1=round(*C1);
	*C2=round(*C2);
	*C3=round(*C3);
}
void ConvertMM_topulse(double *C1,double *C2,double *C3)
{
	*C1=(*C1)*12.50;
	*C2=(*C2)*12.50;
	*C3=(*C3)*9.50;

}
void determinerVecteurTEMPS( double *pos11,double *pos22,double *pos33 ) {

t1=*pos11/vitesseRef1;

t2=*pos22/vitesseRef2;

t3=*pos33/vitesseRef3;
resultats= (t2+t3+t1)/3;
    }
///////////////////////////////////////////////////////////////////////////////////////////
void moveTo( double x,double y,double alpha ){

vitesseRef1=20;
vitesseRef2=20;
vitesseRef3=20;
poszero1=pos1;
poszero2=pos2;
poszero3=pos3;

convert_Frompolar_Tocourse(x, y, alpha);//retourner pos1 POS2 POS3 en mm


if ((pos1 == 0 && pos3 == 0) && pos2 == 0) {
    vitesseRef1 = ceil(poszero1 / resultats);
    vitesseRef2 = ceil(poszero2 / resultats);
    vitesseRef3 = ceil(poszero3 / resultats);
} else {
    ConvertMM_topulse(&pos1, &pos2, &pos3);
    roundpulse(&pos1, &pos2, &pos3);
    determinerVecteurTEMPS(&pos1, &pos2, &pos3);

    vitesseRef1 = ceil(pos1 / resultats);
    vitesseRef2 = ceil(pos2 / resultats);
    vitesseRef3 = ceil(pos3 / resultats);
}

vitesseRef1 = (vitesseRef1 > Vmax) ? Vmax : (vitesseRef1 < Vmin) ? Vmin : vitesseRef1;
vitesseRef2 = (vitesseRef2 > Vmax) ? Vmax : (vitesseRef2 < Vmin) ? Vmin : vitesseRef2;
vitesseRef3 = (vitesseRef3 > Vmax) ? Vmax : (vitesseRef3 < Vmin) ? Vmin : vitesseRef3;




////////////////////////////////////////
while (( (pos2>CountM1)||(pos2>CountM2)||(pos2-CountM1<0)||(pos2-CountM2<0) ||
		(pos1>CountM3)||(pos1>CountM4)||(pos1-CountM3<0)||(pos1-CountM4<0) ||
		(pos3>CountM5)||(pos3>CountM6)||(pos3-CountM5<0)||(pos3-CountM6<0) ))

{
	 //////////////////////////////////////////////////////////MOTEUR1


		 if  ( pos2 -CountM1>0)//>=0.4
		   {

			 HAL_GPIO_WritePin(GPIOC,  AV_RE_M1_Pin, RESET);
			  Regulation_Mt1(speedMotor1, speedMotor2, vitesseRef2, 21);


		   }

		  else if (( pos2 - CountM1   )<0   )//<=-0.5
				{

			  HAL_GPIO_WritePin(GPIOC,  AV_RE_M1_Pin, SET);

			Regulation_Mt1(speedMotor1, speedMotor2, vitesseRef2, 21);


				}


		  else
			{
			  TIM1->CCR1=0;


			}

	///////////////////////////////////////////////////MOTEUR2



		if  (pos2- CountM2>0 )//>=0.4
		   {

			HAL_GPIO_WritePin(GPIOC,  AV_RE_M2_Pin, RESET);
		    Regulation_Mt2(speedMotor2, speedMotor1,vitesseRef2, 21);


		   }else if (( pos2 - CountM2   )<0   )//<=-0.5
				{

			   HAL_GPIO_WritePin(GPIOC,  AV_RE_M2_Pin, SET);

				Regulation_Mt2(speedMotor2, speedMotor1,vitesseRef2, 21);

			    }
		   else
			    {
				 TIM1->CCR2=0;

			    }



	///////////////////////////////////////////////////////////MOTEUR3

			if (pos1 - CountM3 > 0)
			  {

				HAL_GPIO_WritePin(GPIOC, AV_RE_M3_Pin, RESET);

				Regulation_Mt3(  speedMotor3,   speedMotor4, vitesseRef1, 21);
				  //TIM1->CCR3=80;
			   } else if (pos1 - CountM3 < 0)
					   {

				   HAL_GPIO_WritePin(GPIOC, AV_RE_M3_Pin, SET);
				  Regulation_Mt3(  speedMotor3, speedMotor4, vitesseRef1, 21);



			   } else {

				   TIM1->CCR3 = 0;
			   }
/////////////////////////////////////////////////////////////////////////////////MT4

		   if (pos1 - CountM4 > 0)
		   {

			  HAL_GPIO_WritePin(GPIOC, AV_RE_M4_Pin, RESET);

			 Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef1, 21);



		   }
		   else if (pos1 - CountM4 < 0)
		   {

			  HAL_GPIO_WritePin(GPIOC, AV_RE_M4_Pin, SET);

			  Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef1, 21);

		   } else
		   {
			   TIM3->CCR1 = 0;
		   }



	///////////////////////////////////////////////////MOTEUR5

	if (pos3 - CountM5 > 0) {

		HAL_GPIO_WritePin(GPIOC, AV_RE_M5_Pin, RESET);

		  Regulation_Mt5(speedMotor5, speedMotor6, vitesseRef3, 21);


	    } else if (pos3 - CountM5 < 0) {


	    	  HAL_GPIO_WritePin(GPIOC, AV_RE_M5_Pin, SET);
			  Regulation_Mt5(speedMotor5, speedMotor6, vitesseRef3, 21);


	    } else {
	        TIM3->CCR2 = 0;
	    }

////////////////////////////////////////////////////////////////////MT6
	    if (pos3 - CountM6 > 0) {

	    	HAL_GPIO_WritePin(GPIOC, AV_RE_M6_Pin, RESET);
			Regulation_Mt6(speedMotor6, speedMotor5, vitesseRef3, 21);



	    }
	    else if (pos3 - CountM6 < 0)
	    {

	      HAL_GPIO_WritePin(GPIOC, AV_RE_M6_Pin, SET);
		  Regulation_Mt6(speedMotor6, speedMotor5, vitesseRef3, 21);


	    } else
	    {
	        TIM3->CCR3 = 0;
	    }

}
////////////////////////////////////////////////////////////////////////////
   TIM1->CCR1 = (pos2 - CountM1 == 0) ? 0 : TIM1->CCR1;
   TIM1->CCR2 = (pos2 - CountM2 == 0) ? 0 : TIM1->CCR2;

	 			if  (( pos1  -CountM3  )==0 )
				   {
					  TIM1->CCR3=0;

				   }
				if  (( pos1  -CountM4 )==0 )
				   {
					TIM3->CCR1 =0;

					}
				if  (( pos3  -CountM5  )==0 )
				    {
					 TIM3->CCR2=0;

					 }
				if  (( pos3 -CountM6  )==0 )
					 {
					TIM3->CCR3 =0;

					 }
}

void convert_Frompolar_Tocourse(double x, double y, double alpha){

alpha=PI*alpha/180;// angle radian
pos1=sqrt(pow(x+185*sin(alpha)-63*cos(alpha),2)+pow(y+185*cos(alpha)+63*sin(alpha),2))-356;// EQUATION COURSE1
pos2=sqrt(pow(x+185*sin(alpha)-63*cos(alpha)+100,2)+pow(y+185*cos(alpha)+63*sin(alpha),2))-356;//EQUATION COURSE 2
pos3=sqrt(pow(x+185*sin(alpha)+63*cos(alpha)-100,2)+pow(y+185*cos(alpha)-63*sin(alpha),2))-356;// EQUATION COURSE3
if(pos1<0){pos1=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course
if(pos2<0){pos2=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course
if(pos3<0){pos3=0;}// MOUVE TO ZERO POSITION (x	=0 y=0 alpha=0) donne des resultats negative de course

}

void Commander_Moteuraxial(){

	 int v1 = HAL_GPIO_ReadPin(GPIOC, Capt_axial1_Pin);
	 int v2 = HAL_GPIO_ReadPin(GPIOC, Capt_axial2_Pin);

	   if(v1==GPIO_PIN_SET )
	   {

		  HAL_GPIO_WritePin(GPIOA,  AV_RE_axe_x_Pin, RESET);
		  TIM3->CCR4=50;

	    }else if (v2 ==GPIO_PIN_SET)
	    {
	  		HAL_GPIO_WritePin(GPIOA,  AV_RE_axe_x_Pin, SET);
			TIM3->CCR4=50;


	    }

}
void zerodefine(){
    moveTo(0, -605, 0);

    while(current<1.2 )
            {
        Regulation_Mt6(speedMotor6, speedMotor5, 11, 21);
        Regulation_Mt5(speedMotor5, speedMotor6, 11, 21);
        Regulation_Mt1(speedMotor1, speedMotor2, vitesseRef1, 21) ;
        Regulation_Mt2(speedMotor2, speedMotor1, vitesseRef1, 21);
        Regulation_Mt3(speedMotor3, speedMotor4, vitesseRef2, 21);
        Regulation_Mt4(speedMotor4, speedMotor3, vitesseRef2, 21);



        	}

    	TIM1->CCR1 =0; //MT1
    	TIM1->CCR2 =0;//MT2
    	TIM1->CCR3 =0;//MT3

    	TIM3->CCR1 =0;//MT4
    	TIM3->CCR2 =0;//MT5
    	TIM3->CCR3 =0;//MT6

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
  // start the adc

HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);


HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
//PB1
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
//PA1
HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);


TIM1->CCR1 =0; //MT1
TIM1->CCR2 =0;//MT2
TIM1->CCR3 =0;//MT3

TIM3->CCR1 =0;//MT4
TIM3->CCR2 =0;//MT5
TIM3->CCR3 =0;//MT6
TIM3->CCR4=0;// MOTEUR AXIAL
//moteur1
HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);//PA0 START INTERRUPTION
HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);//PA2 START INTERRUPTION
HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);//PB3 START INTERRUPTION

//moteur2
HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);//PC7


//moteur3
HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);//PB6
//moteur4
HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);//PB7
//moteur5
HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);//PB8
//moteur6
HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);//PB9

// BATTERY

HAL_ADC_Start_DMA(&hadc2, &readValue, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  TIM3->CCR4 =25; //MT1
	 	  TIM12->CCR1 =30; //MT1

    /* USER CODE BEGIN 3 */

}
    /* USER CODE BEGIN 3 */

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
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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