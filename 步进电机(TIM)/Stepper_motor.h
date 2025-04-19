//
// Created by 星必尘Sguan on 2025/4/10.
//

#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "stm32f1xx_hal.h"

void StepperMotor_Contrl(int32_t Velocity, int32_t Step);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif //__STEPPER_MOTOR_H
