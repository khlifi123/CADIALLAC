/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define rotation1_Pin GPIO_PIN_2
#define rotation1_GPIO_Port GPIOE
#define rotation2_Pin GPIO_PIN_3
#define rotation2_GPIO_Port GPIOE
#define rotation3_Pin GPIO_PIN_4
#define rotation3_GPIO_Port GPIOE
#define rotation4_Pin GPIO_PIN_5
#define rotation4_GPIO_Port GPIOE
#define Capt_axial1_Pin GPIO_PIN_0
#define Capt_axial1_GPIO_Port GPIOF
#define Capt_axial2_Pin GPIO_PIN_1
#define Capt_axial2_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define AV_R_R1_Pin GPIO_PIN_0
#define AV_R_R1_GPIO_Port GPIOC
#define AV_R_R2_Pin GPIO_PIN_1
#define AV_R_R2_GPIO_Port GPIOC
#define AV_R_R3_Pin GPIO_PIN_2
#define AV_R_R3_GPIO_Port GPIOC
#define AV_R_R4_Pin GPIO_PIN_3
#define AV_R_R4_GPIO_Port GPIOC
#define AV_R_desc_Pin GPIO_PIN_6
#define AV_R_desc_GPIO_Port GPIOC
#define AV_R_ax_Pin GPIO_PIN_7
#define AV_R_ax_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
