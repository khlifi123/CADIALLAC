/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Retracted_S4_Pin GPIO_PIN_0
#define Retracted_S4_GPIO_Port GPIOF
#define Retracted_S3_Pin GPIO_PIN_1
#define Retracted_S3_GPIO_Port GPIOF
#define Courant_V5_Pin GPIO_PIN_6
#define Courant_V5_GPIO_Port GPIOF
#define Courant_V6_Pin GPIO_PIN_7
#define Courant_V6_GPIO_Port GPIOF
#define VINB1_Pin GPIO_PIN_0
#define VINB1_GPIO_Port GPIOC
#define VINB2_Pin GPIO_PIN_1
#define VINB2_GPIO_Port GPIOC
#define VINB3_Pin GPIO_PIN_2
#define VINB3_GPIO_Port GPIOC
#define VINB4_Pin GPIO_PIN_3
#define VINB4_GPIO_Port GPIOC
#define Courant_V1_Pin GPIO_PIN_1
#define Courant_V1_GPIO_Port GPIOA
#define Courant_V2_Pin GPIO_PIN_2
#define Courant_V2_GPIO_Port GPIOA
#define Courant_V4_Pin GPIO_PIN_3
#define Courant_V4_GPIO_Port GPIOA
#define BATTERIE_Pin GPIO_PIN_4
#define BATTERIE_GPIO_Port GPIOA
#define Courant_V3_Pin GPIO_PIN_5
#define Courant_V3_GPIO_Port GPIOA
#define VINB5_Pin GPIO_PIN_4
#define VINB5_GPIO_Port GPIOC
#define VINB6_Pin GPIO_PIN_5
#define VINB6_GPIO_Port GPIOC
#define START_Pin GPIO_PIN_0
#define START_GPIO_Port GPIOB
#define Led_Level_BATT_Pin GPIO_PIN_1
#define Led_Level_BATT_GPIO_Port GPIOB
#define Retracted_S2_Pin GPIO_PIN_0
#define Retracted_S2_GPIO_Port GPIOG
#define Retracted_S1_Pin GPIO_PIN_1
#define Retracted_S1_GPIO_Port GPIOG
#define rotation3_Pin GPIO_PIN_15
#define rotation3_GPIO_Port GPIOA
#define rotation1_Pin GPIO_PIN_10
#define rotation1_GPIO_Port GPIOC
#define rotation2_Pin GPIO_PIN_11
#define rotation2_GPIO_Port GPIOC
#define Retracted_S6_Pin GPIO_PIN_0
#define Retracted_S6_GPIO_Port GPIOD
#define Retracted_S5_Pin GPIO_PIN_1
#define Retracted_S5_GPIO_Port GPIOD
#define rotation4_Pin GPIO_PIN_5
#define rotation4_GPIO_Port GPIOD
#define rotation5_Pin GPIO_PIN_6
#define rotation5_GPIO_Port GPIOD
#define rotation6_Pin GPIO_PIN_7
#define rotation6_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
