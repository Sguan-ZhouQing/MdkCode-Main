#ifndef AHT20_DMA_H
#define AHT20_DMA_H

#include "stm32f4xx_hal.h"

#define AHT20_I2C_ADDRESS         0x38 << 1  // 7位地址左移1位

// 命令定义
#define AHT20_INIT_CMD            0xBE
#define AHT20_TRIGGER_MEASURE_CMD 0xAC
#define AHT20_SOFT_RESET_CMD      0xBA
#define AHT20_READ_STATUS_CMD     0x71

// 状态位定义
#define AHT20_STATUS_BUSY_BIT     0x80
#define AHT20_STATUS_CAL_ENABLED  0x08

// 测量参数
#define AHT20_MEASURE_PARAM1      0x33
#define AHT20_MEASURE_PARAM2      0x00
#define AHT20_INIT_PARAM1         0x08
#define AHT20_INIT_PARAM2         0x00

// 状态机状态定义
typedef enum {
    AHT20_STATE_IDLE,
    AHT20_STATE_INIT_CHECK,
    AHT20_STATE_INIT,
    AHT20_STATE_TRIGGER_MEASURE,
    AHT20_STATE_WAIT_MEASURE,
    AHT20_STATE_READ_DATA,
    AHT20_STATE_READY,
    AHT20_STATE_ERROR
} AHT20_State;

typedef struct {
    float temperature;
    float humidity;
} AHT20_Data;

typedef struct {
    I2C_HandleTypeDef *hi2c;
    AHT20_State state;
    uint32_t measure_start_time;
    uint8_t raw_data[6];
    uint8_t status;
    AHT20_Data data;
    uint8_t initialized;
} AHT20_Handle;

// 函数声明
void AHT20_Init_DMA(AHT20_Handle *handle, I2C_HandleTypeDef *hi2c);
void AHT20_Process(AHT20_Handle *handle);
HAL_StatusTypeDef AHT20_StartMeasurement_DMA(AHT20_Handle *handle);
uint8_t AHT20_IsDataReady(AHT20_Handle *handle);
AHT20_Data AHT20_GetData(AHT20_Handle *handle);
void AHT20_Reset(AHT20_Handle *handle);

#endif // AHT20_DMA_H
