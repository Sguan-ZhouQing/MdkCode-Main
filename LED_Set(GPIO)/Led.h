#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "gpio.h"

typedef struct
{

	_Bool Led_Status;

} LED_INFO;

#define LED_ON		1

#define LED_OFF	0

extern LED_INFO led_info;

void Led_Set(_Bool status);

#endif
