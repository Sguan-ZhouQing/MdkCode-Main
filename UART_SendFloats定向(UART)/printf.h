#ifndef __PRINTF_H
#define __PRINTF_H

#include "stm32f4xx_hal.h"

#define esp_BUFFER_SIZE 256

void UART_SendFloats(float *data, uint8_t count, uint8_t decimal_places);


#endif // PRINTF_H

