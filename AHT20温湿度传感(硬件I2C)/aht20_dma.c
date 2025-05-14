#include "aht20_dma.h"
#include "main.h"
#include <math.h>

/**
  * @brief 初始化AHT20传感器处理结构体
  * @param handle AHT20处理结构体指针
  * @param hi2c I2C句柄指针
  */
void AHT20_Init_DMA(AHT20_Handle *handle, I2C_HandleTypeDef *hi2c) {
    handle->hi2c = hi2c;
    handle->state = AHT20_STATE_IDLE;
    handle->initialized = 0;
    handle->measure_start_time = 0;
    handle->data.temperature = 0;
    handle->data.humidity = 0;
}

/**
  * @brief 启动测量流程
  * @param handle AHT20处理结构体指针
  * @retval HAL状态
  */
HAL_StatusTypeDef AHT20_StartMeasurement_DMA(AHT20_Handle *handle) {
    if (handle->state != AHT20_STATE_IDLE && handle->state != AHT20_STATE_READY) {
        return HAL_BUSY;
    }
    
    if (!handle->initialized) {
        handle->state = AHT20_STATE_INIT_CHECK;
    } else {
        handle->state = AHT20_STATE_TRIGGER_MEASURE;
    }
    
    return HAL_OK;
}

/**
  * @brief 主处理函数，应在主循环中定期调用
  * @param handle AHT20处理结构体指针
  */
void AHT20_Process(AHT20_Handle *handle) {
    uint8_t cmd[3];
    
    switch (handle->state) {
        case AHT20_STATE_IDLE:
            // 空闲状态，不做任何操作
            break;
            
        case AHT20_STATE_INIT_CHECK:
            // 检查初始化状态
            cmd[0] = AHT20_READ_STATUS_CMD;
            if (HAL_I2C_Master_Transmit_DMA(handle->hi2c, AHT20_I2C_ADDRESS, cmd, 1) == HAL_OK) {
                handle->state = AHT20_STATE_WAIT_READ_STATUS;
            } else {
                handle->state = AHT20_STATE_ERROR;
            }
            break;
            
        case AHT20_STATE_WAIT_READ_STATUS:
            // 等待状态读取完成（在回调函数中处理）
            break;
            
        case AHT20_STATE_INIT:
            // 发送初始化命令
            cmd[0] = AHT20_INIT_CMD;
            cmd[1] = AHT20_INIT_PARAM1;
            cmd[2] = AHT20_INIT_PARAM2;
            if (HAL_I2C_Master_Transmit_DMA(handle->hi2c, AHT20_I2C_ADDRESS, cmd, 3) == HAL_OK) {
                handle->state = AHT20_STATE_WAIT_INIT;
            } else {
                handle->state = AHT20_STATE_ERROR;
            }
            break;
            
        case AHT20_STATE_WAIT_INIT:
            // 等待初始化完成（10ms后继续）
            if (HAL_GetTick() - handle->measure_start_time > 10) {
                handle->initialized = 1;
                handle->state = AHT20_STATE_TRIGGER_MEASURE;
            }
            break;
            
        case AHT20_STATE_TRIGGER_MEASURE:
            // 触发测量
            cmd[0] = AHT20_TRIGGER_MEASURE_CMD;
            cmd[1] = AHT20_MEASURE_PARAM1;
            cmd[2] = AHT20_MEASURE_PARAM2;
            if (HAL_I2C_Master_Transmit_DMA(handle->hi2c, AHT20_I2C_ADDRESS, cmd, 3) == HAL_OK) {
                handle->measure_start_time = HAL_GetTick();
                handle->state = AHT20_STATE_WAIT_MEASURE;
            } else {
                handle->state = AHT20_STATE_ERROR;
            }
            break;
            
        case AHT20_STATE_WAIT_MEASURE:
            // 等待测量完成（75ms）
            if (HAL_GetTick() - handle->measure_start_time > 75) {
                handle->state = AHT20_STATE_READ_DATA;
            }
            break;
            
        case AHT20_STATE_READ_DATA:
            // 读取数据
            cmd[0] = AHT20_READ_STATUS_CMD;
            if (HAL_I2C_Master_Transmit_DMA(handle->hi2c, AHT20_I2C_ADDRESS, cmd, 1) == HAL_OK) {
                handle->state = AHT20_STATE_WAIT_READ_DATA;
            } else {
                handle->state = AHT20_STATE_ERROR;
            }
            break;
            
        case AHT20_STATE_WAIT_READ_DATA:
            // 等待数据读取完成（在回调函数中处理）
            break;
            
        case AHT20_STATE_READY:
            // 数据就绪，等待应用程序读取
            break;
            
        case AHT20_STATE_ERROR:
            // 错误状态，需要重置
            break;
    }
}

/**
  * @brief 检查数据是否就绪
  * @param handle AHT20处理结构体指针
  * @retval 数据就绪状态
  */
uint8_t AHT20_IsDataReady(AHT20_Handle *handle) {
    return (handle->state == AHT20_STATE_READY);
}

/**
  * @brief 获取测量数据
  * @param handle AHT20处理结构体指针
  * @retval 温湿度数据
  */
AHT20_Data AHT20_GetData(AHT20_Handle *handle) {
    if (handle->state == AHT20_STATE_READY) {
        handle->state = AHT20_STATE_IDLE;
        return handle->data;
    }
    AHT20_Data invalid_data = {NAN, NAN};
    return invalid_data;
}

/**
  * @brief 重置传感器状态
  * @param handle AHT20处理结构体指针
  */
void AHT20_Reset(AHT20_Handle *handle) {
    handle->state = AHT20_STATE_IDLE;
    handle->initialized = 0;
}

/**
  * @brief I2C传输完成回调函数
  * @param hi2c I2C句柄指针
  */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    // 需要在用户代码中实现，并调用AHT20_TxCpltCallback
}

/**
  * @brief I2C接收完成回调函数
  * @param hi2c I2C句柄指针
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    // 需要在用户代码中实现，并调用AHT20_RxCpltCallback
}

/**
  * @brief AHT20传输完成回调
  * @param handle AHT20处理结构体指针
  */
void AHT20_TxCpltCallback(AHT20_Handle *handle) {
    if (handle->state == AHT20_STATE_WAIT_READ_STATUS) {
        // 状态读取传输完成，开始接收状态字节
        if (HAL_I2C_Master_Receive_DMA(handle->hi2c, AHT20_I2C_ADDRESS, &handle->status, 1) != HAL_OK) {
            handle->state = AHT20_STATE_ERROR;
        }
    } else if (handle->state == AHT20_STATE_WAIT_READ_DATA) {
        // 数据读取传输完成，开始接收6字节数据
        if (HAL_I2C_Master_Receive_DMA(handle->hi2c, AHT20_I2C_ADDRESS, handle->raw_data, 6) != HAL_OK) {
            handle->state = AHT20_STATE_ERROR;
        }
    }
}

/**
  * @brief AHT20接收完成回调
  * @param handle AHT20处理结构体指针
  */
void AHT20_RxCpltCallback(AHT20_Handle *handle) {
    if (handle->state == AHT20_STATE_WAIT_READ_STATUS) {
        // 状态字节接收完成
        if ((handle->status & AHT20_STATUS_CAL_ENABLED) == 0) {
            // 需要初始化
            handle->state = AHT20_STATE_INIT;
        } else {
            // 已初始化，直接触发测量
            handle->initialized = 1;
            handle->state = AHT20_STATE_TRIGGER_MEASURE;
        }
    } else if (handle->state == AHT20_STATE_WAIT_READ_DATA) {
        // 数据接收完成，解析数据
        uint32_t humidity_raw = ((uint32_t)handle->raw_data[1] << 12) | 
                              ((uint32_t)handle->raw_data[2] << 4) | 
                              ((handle->raw_data[3] & 0xF0) >> 4);
        uint32_t temperature_raw = ((uint32_t)(handle->raw_data[3] & 0x0F) << 16) | 
                                 ((uint32_t)handle->raw_data[4] << 8) | 
                                 handle->raw_data[5];
        
        handle->data.humidity = (float)humidity_raw * 100.0f / (1 << 20);
        handle->data.temperature = (float)temperature_raw * 200.0f / (1 << 20) - 50.0f;
        
        handle->state = AHT20_STATE_READY;
    }
}

