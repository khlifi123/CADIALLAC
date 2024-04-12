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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define frequencyM1     1000/(periodMotor1)    // FREQUENCE DU L ENCODEUR 1
#define frequencyM2     1000/(periodMotor2)    // FREQUENCE DU L ENCODEUR 2
#define frequencyM3     1000/(periodMotor3)    // FREQUENCE DU L ENCODEUR 3
#define frequencyM4     1000/(periodMotor4)    // FREQUENCE DU L ENCODEUR 4
#define frequencyM5     1000/(periodMotor5)    // FREQUENCE DU L ENCODEUR 5
#define frequencyM6     1000/(periodMotor6)    // FREQUENCE DU L ENCODEUR 6
#define   Vmax           30
#define   Vmin           17
void pressbouton();
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
#define IMPULSION_TO_COURSE24  CountM1/12.5
#define IMPULSION_TO_COURSE12 CountM2/9.5

uint32_t moyenne = 0;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	  if(htim->Instance==TIM2)
	  {
		  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)// MOTEUR 1

		  	{
			     CountM1++;


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

		  	}
		  if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)// MOTEUR 1
		  {


									CountM2+=1;

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

}
void pressbouton(){


    if (HAL_GPIO_ReadPin(GPIOC, bouton_Pin) == GPIO_PIN_SET) {
		    if (CountM1<10) {

	    	TIM1->CCR1 =25; //MT1

    /* USER CODE BEGIN 3 */
               }else if (CountM1>=10) {
	             TIM1->CCR1 =0; //MT1


  }
		    if (CountM2<12) {

		    	TIM1->CCR2 =100; //MT1

	    /* USER CODE BEGIN 3 */
	               }else if (CountM2>=12) {
		             TIM1->CCR2 =0; //MT1


	  }


}
    if (HAL_GPIO_ReadPin(GPIOC, BTMONTER_Pin) == GPIO_PIN_SET) {
    	HAL_GPIO_WritePin(GPIOC, DIR1_Pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin(GPIOC, DIR2_Pin, GPIO_PIN_SET);


    		    if (CountM1<10) {

    	    	TIM1->CCR1 =25; //MT1

        /* USER CODE BEGIN 3 */
                   }else if (CountM1>=10) {
    	             TIM1->CCR1 =0; //MT1


      }
    		    if (CountM2<12) {

    		    	TIM1->CCR2 =100; //MT1

    	    /* USER CODE BEGIN 3 */
    	               }else if (CountM2>=12) {
    		             TIM1->CCR2 =0; //MT1


    	  }


    }

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);//PA0 START INTERRUPTION
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);//PA1 START INTERRUPTION
	TIM1->CCR1 =0; //MT1
  	TIM1->CCR2 =0;//MT2
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */
pressbouton();
    /* USER CODE BEGIN 3 */
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

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 45-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 90-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DIR1_Pin|DIR2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : bouton_Pin BTMONTER_Pin */
  GPIO_InitStruct.Pin = bouton_Pin|BTMONTER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DIR1_Pin DIR2_Pin */
  GPIO_InitStruct.Pin = DIR1_Pin|DIR2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
