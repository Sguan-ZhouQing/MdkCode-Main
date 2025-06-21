#ifndef __ESP_H
#define __ESP_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>  // 确保包含此头文件以使用 uint32_t
#include <string.h>


#define Esp_EN_Port GPIOB      
#define Esp_EN GPIO_PIN_0       //cubeMX在配置的过程中,EN引脚高电平有效（长时间要高电平）
#define Esp_RST_Port GPIOB
#define Esp_RST GPIO_PIN_1      //RST引脚低电平有效，默认拉高了的（长时间要高电平）


typedef enum
{
  Esp_OK       = 0x00U,
  Esp_ERROR    = 0x01U,
} Esp_StatusTypeDef;


static void ESP_SendString(const char *Str);
Esp_StatusTypeDef ESP_Init(void);


#endif
