#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f1xx_hal.h"

int Read_MotorCounter(TIM_HandleTypeDef *htim);
void Read_Speed(void);

#endif
