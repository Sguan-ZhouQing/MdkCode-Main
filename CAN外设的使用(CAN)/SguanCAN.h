#ifndef __SGUANCAN_H
#define __SGUANCAN_H

#include "stm32f1xx_hal.h"

HAL_StatusTypeDef SguanCAN_FilterInit(void);
HAL_StatusTypeDef SguanCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data);
uint8_t SguanCAN_ReceiveFlag(void);
void SguanCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data);

#endif // SGUANCAN_H
