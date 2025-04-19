#ifndef __STRESSSENSING_H
#define __STRESSSENSING_H

#include "stm32g4xx_hal.h"

#define ADC_BUFFER_SIZE 32
extern float Stress_voltage;
extern uint32_t adcBuffer[ADC_BUFFER_SIZE];

void StressSensing_Init(void);
float Stress_GetValue(void);
float Stress_GetValue_DMA(void);

#endif

