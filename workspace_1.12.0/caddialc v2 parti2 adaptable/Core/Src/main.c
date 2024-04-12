/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "interruption.h"
#include "asservissement.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define frequencyM1     1000/(periodMotor1)    // FREQUENCE DU L ENCODEUR 1
#define frequencyM2     1000/(periodMotor2)    // FREQUENCE DU L ENCODEUR 2
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float speedMotor1=0;
float speedMotor2=0;
uint16_t periodMotor1=0;
uint16_t periodMotor2=0;
volatile float Is_First_Captured1=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 1 EST DETECTE
volatile float Is_First_Captured2=0;// VARIABLE POUR TESTER SILE FRONT MONTANT DU L ENCODEUR 2 EST DETECTE
volatile int IC1_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 1
volatile int IC2_Val1=0;        //VARIABLE POUR STOCKER LA VALEUR DU  FRONT MONTANT DU L ENCODEUR 2
volatile int CountMR1=0; // NOMBRE D IMPULSION ENCODEUR1
volatile int CountMR2=0; // NOMBRE D IMPULSION ENCODEUR2
volatile float CourantR1;
volatile float CourantR2;
uint16_t buffer2[1];
uint16_t buffer3[2];
int sum=0;
float PWM_MEULE;
float moyenne=0;
int i=0;
uint8_t senddata[4] = {0x66, 0x42, 0x00,0xA8};//TX UART avec bldc
uint8_t trame[1];//RX UART from bldc
float CUR_MTMeule;
uint8_t senddataPOS_encour[1]={0x21};// 101 : 10 =ST2  et 1 cad ok
uint8_t Msgsenthold_ToST1[1]={0xF0};// 100 : 10 =ST2  et 0 cad nok
uint8_t MsgsentTerminé_ToST1[1]={44};// 100 : 10 =ST2  et 0 cad nok

uint8_t MsgrecuSt1[1];

int RawValueB;
int OffsetB;
float VoltageB;
float AmpCurrentB = 0;
uint16_t samples1[10];
float vitesse1_average=0;
uint32_t vitesse1_sum = 0;
uint16_t samples2[10];
float vitesse2_average=0;
uint32_t vitesse2_sum = 0;
float current;

uint16_t readValue1;
uint16_t readValue2;
uint16_t readValue3;

uint8_t seuil=0;

uint32_t temp=0;
float PWM_M;
uint8_t POSzero=0;
int j=0;
int pos1;
int pos2;
int readings[10];   // Tableau pour stocker les lectures précédentes
int compteur = 0;               // Index pour parcourir le tableau
int total = 0;               // Total des lectures
float average=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void moveroleauTo(int pos1, int pos2 );
float calculateMovingAverage(float newValue);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)

{

	  if(htim->Instance==TIM3)

	  {

            if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)	//Roleau1

				{
				Interruption_1();

					if (Is_First_Captured1 == 0)
						{
							IC1_Val1=HAL_GetTick();
							Is_First_Captured1++;
						}
					else if (Is_First_Captured1 == 1)
						{
							periodMotor1 = HAL_GetTick()-IC1_Val1;//periode1
							if(periodMotor1>1)
							{
							  speedMotor1 = frequencyM1;
							}
							Is_First_Captured1 = 0;

						}

				}



	  		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)//Roleau2
	  			  {
	  			     Interruption_2();

					   if (Is_First_Captured2 == 0)
						   {
								IC2_Val1=HAL_GetTick();
								Is_First_Captured2++;
						   }
						else if (Is_First_Captured2== 1)
							{
								periodMotor2 = HAL_GetTick()-IC2_Val1;//periode1periode1*0.5 both edge
							    if(periodMotor2>1)
							    {
								  speedMotor2 = frequencyM2;
								}
								Is_First_Captured2 = 0;

							}

					}






	  	}

}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	HAL_ADC_Start_IT(&hadc3);
  	HAL_ADC_Start_IT(&hadc2);
    HAL_ADC_Start_IT(&hadc1);

	if(hadc->Instance==ADC1){
		readValue1 = HAL_ADC_GetValue (&hadc1);

	}if(hadc->Instance==ADC2){
		readValue2 = HAL_ADC_GetValue (&hadc2);
		VoltageB=(readValue2*3.3)/4095;
		current=(VoltageB-2.5)*10;
		 average = calculateMovingAverage(current);


	}if(hadc->Instance==ADC3){
		readValue3 = HAL_ADC_GetValue (&hadc3);


	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
  {

	HAL_UART_Receive_IT(&huart1,MsgrecuSt1, 1);//recevoir 1 du stm1 pos xy alpha terminé;
	HAL_UART_Receive_IT(&huart3,trame, 1);//recevoir trame du bldc;
	//CUR_MTMeule=trame[0];

  }

void sendParameter()
  {

     HAL_UART_Transmit_IT(&huart3, senddata, 4);// send data to bldc
    HAL_Delay(150);
  }
void Mise_a_zero_encours()
  {

     HAL_UART_Transmit_IT(&huart1, senddataPOS_encour, 1);
     HAL_Delay(100);
  }

void sendholdTo_st1()
  {

     HAL_UART_Transmit_IT(&huart1, Msgsenthold_ToST1, 1);
     HAL_Delay(100);
  }
void sendterminé_st1()
  {

     HAL_UART_Transmit_IT(&huart1, MsgsentTerminé_ToST1, 1);
     HAL_Delay(100);
  }
void zero(){
	 if ( MsgrecuSt1[0] == 0x1F)//
		      {

		    	   while(CountMR1<630 || CountMR2<660)
		    		{

		    		   if(CountMR2<660)//510
						  {
		    			 HAL_GPIO_WritePin(GPIOB, dir2_Pin, GPIO_PIN_RESET);
							  TIM2->CCR1 = 100;
						  } else
						  {
							  TIM2->CCR1= 0;

						  }

		    		   if(CountMR1<630)
						  {
		       	    	HAL_GPIO_WritePin(GPIOB,  dir1_Pin, GPIO_PIN_RESET);

							  TIM2->CCR2 = 100;
						  } else
						  {
							  TIM2->CCR2= 0;

						  }

		    		}
		    	   if(CountMR1>=630)
					  {
		    		   TIM2->CCR2= 0;
					  }
		    	   if(CountMR2>=660)
					  {
					   TIM2->CCR1= 0;
					  }



			       TIM4->CCR1=42;
                   HAL_Delay(3000);

		    	   Mise_a_zero_encours();// send 0X21 to st1 pour  avancer 1mm




		 }

	 while((MsgrecuSt1[0] ==0x11) && trame[0]<(seuil+3))// si POS ST1 AVANCEE 1 MM EST TERMINe
	      {
	 		   pos1=CountMR1-8;
	 		   pos2=CountMR2-8;
	 		   moveroleauTo(pos1,pos2);// RECULER LES R 1MM

	      }
	 	if( trame[0]>=(seuil+3)){
	 		sendholdTo_st1();//HOLD send 4
	 		TIM4->CCR1=36;
	 		TIM2->CCR1 = 0;
	 		TIM2->CCR2 = 0;


	 	 }


}


void moveroleauTo(int pos1, int pos2) {
	while (((pos1 != CountMR1) || (pos2 != CountMR2))&& trame[0]<(seuil+3)) {
		// Mouvement pour le vérin 2
		if (pos2 > CountMR2) {
			HAL_GPIO_WritePin(GPIOB, dir1_Pin, GPIO_PIN_RESET); // Avancer
			TIM2->CCR1 = 50;
		} else if (pos2 < CountMR2) {
			HAL_GPIO_WritePin(GPIOB, dir1_Pin, GPIO_PIN_SET); // Reculer
			TIM2->CCR1 = 50;
		} else {
			TIM2->CCR1 = 0; // Arrêter
		}

		// Mouvement pour le vérin 1
		if (pos1 > CountMR1) {
			HAL_GPIO_WritePin(GPIOB, dir2_Pin, GPIO_PIN_RESET); // Avancer
			TIM2->CCR2 = 50;
		} else if (pos1 < CountMR1) {
			HAL_GPIO_WritePin(GPIOB, dir2_Pin, GPIO_PIN_SET); // Reculer
			TIM2->CCR2 = 50;
		} else {
			TIM2->CCR2 = 0; // Arrêter
		}
	}

	// Arrêter les vérins une fois qu'ils ont atteint leur position cible

	if (pos1 == CountMR1) {
		TIM2->CCR2 = 0;
	}
	if (pos2 == CountMR2) {
		TIM2->CCR1 = 0;

	}
}
float calculateMovingAverage(float newValue) {
  // Soustraire la lecture la plus ancienne
  total = total - readings[compteur];
  // Stocker la nouvelle lecture dans le tableau
  readings[compteur] = newValue;
  // Ajouter la nouvelle lecture au total
  total = total + newValue;
  // Incrémenter l'index en boucle
  compteur = (compteur + 1) % 10;
  // Calculer la moyenne mobile

  return total / (float)10;
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
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  //moteur1
    	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);//
    	//moteur2
    	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);//

    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//MTr1
    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//MTr2

    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//MTMEULE
    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//MTDSE

    HAL_UART_Receive_IT(&huart1,MsgrecuSt1, 1);//sizeof(buffer));
	HAL_UART_Receive_IT(&huart3,trame, 1);//sizeof(buffer));
  	//HAL_ADC_Start_IT(&hadc1);
  	HAL_ADC_Start_IT(&hadc2);
  	//HAL_ADC_Start_IT(&hadc3);
	      TIM4->CCR1=36;
		  HAL_Delay(1000);

		  TIM4->CCR1=42;
		  HAL_Delay(4000);
	      seuil=trame[0];
		  TIM4->CCR1=36;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	 zero();
	 pos1=CountMR1+10;
	 pos2=CountMR2+10;
	//

	while(MsgrecuSt1[0]==0xF0){
		moveroleauTo(pos1, pos2);

		 //  HAL_Delay(8000);
		  // TIM4->CCR1=55;

// process of grinding

	}
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
