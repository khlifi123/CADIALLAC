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
#include "stm32f4xx_hal.h"

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
#define rotation4_Pin GPIO_PIN_13
#define rotation4_GPIO_Port GPIOC
#define AV_RE_M1_Pin GPIO_PIN_0
#define AV_RE_M1_GPIO_Port GPIOC
#define AV_RE_M2_Pin GPIO_PIN_1
#define AV_RE_M2_GPIO_Port GPIOC
#define AV_RE_M3_Pin GPIO_PIN_2
#define AV_RE_M3_GPIO_Port GPIOC
#define AV_RE_axe_x_Pin GPIO_PIN_5
#define AV_RE_axe_x_GPIO_Port GPIOA
#define AV_RE_M4_Pin GPIO_PIN_4
#define AV_RE_M4_GPIO_Port GPIOC
#define AV_RE_M5_Pin GPIO_PIN_5
#define AV_RE_M5_GPIO_Port GPIOC
#define rotation5_Pin GPIO_PIN_2
#define rotation5_GPIO_Port GPIOB
#define rotation6_Pin GPIO_PIN_10
#define rotation6_GPIO_Port GPIOB
#define AV_RE_M6_Pin GPIO_PIN_6
#define AV_RE_M6_GPIO_Port GPIOC
#define Capt_axial2_Pin GPIO_PIN_8
#define Capt_axial2_GPIO_Port GPIOC
#define Capt_axial1_Pin GPIO_PIN_9
#define Capt_axial1_GPIO_Port GPIOC
#define rotation3_Pin GPIO_PIN_15
#define rotation3_GPIO_Port GPIOA
#define rotation1_Pin GPIO_PIN_10
#define rotation1_GPIO_Port GPIOC
#define rotation2_Pin GPIO_PIN_11
#define rotation2_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */