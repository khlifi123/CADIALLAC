/*
 * File: DC_MOTOR_cfg.h
 * Driver Name: [[ DC MOTOR ]]
  * SW Layer:   verin
 * Created on:2023
 * Ver: 1.0
 * Author:     khlifi

 */

#ifndef DC_MOTOR_CFG_H_
#define DC_MOTOR_CFG_H_
#define DC_MOTOR_UNITS 6
#include "DC_MOTOR.h"
typedef struct {
	GPIO_TypeDef * DIR1_GPIO;
	GPIO_TypeDef * DIR2_GPIO;

    uint16_t       DIR1_PIN;
    uint16_t       DIR2_PIN;

    TIM_TypeDef* TIM_Instance;
    uint32_t PWM_TIM_CH;
} DC_MOTOR_CfgType;

extern const DC_MOTOR_CfgType DC_MOTOR_CfgParam[DC_MOTOR_UNITS];



#endif /* MOTEUR_CONFIG_H */
