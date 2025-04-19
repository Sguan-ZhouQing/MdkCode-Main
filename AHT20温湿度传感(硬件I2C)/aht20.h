#ifndef __AHT20_H
#define __AHT20_H

#include "stm32f1xx_hal.h"
#include "i2c.h"

void AHT20_Red(float *Temperature , float *Humidity);
void AHT20_Int(void);



#endif
