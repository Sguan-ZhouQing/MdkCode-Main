/*
 * @Author: 星必尘Sguan
 * @Date: 2025-04-16 16:32:32
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-04-16 18:04:39
 * @FilePath: \test_StressSensing\Hardware\StressSensing.c
 * @Description: HAL
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "StressSensing.h"

extern ADC_HandleTypeDef hadc1;
uint32_t adcBuffer[ADC_BUFFER_SIZE];
float Stress_voltage;


/**
 * @description: DMA开启函数，要在cubeMX中开启DMA循环模式;
 * @return {*}
 */
void StressSensing_Init(void) 
{
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcBuffer, ADC_BUFFER_SIZE);  // 循环模式
}


/**
 * @description: ADC采样，读取模拟电压值变化大小;
 * @return {*}
 */
float Stress_GetValue(void)
{
    float temp;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY);
    uint32_t raw_val = HAL_ADC_GetValue(&hadc1);
    temp = raw_val*(3.3f - 0.0f)/4095.0f;
    return temp;
}


/**
 * @description: (ADC模拟电压)直接读取DMA缓冲区的最新值
 * @return {*}
 */
float Stress_GetValue_DMA(void) 
{
    uint32_t raw_val = adcBuffer[0] & 0xFFF;  // 确保提取12位有效值
    return raw_val * 3.3f / 4095.0f;
}


/**
 * @description: DMA方式的ADC采样回调函数;
 * @param {ADC_HandleTypeDef*} hadc
 * @return {*}
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) 
{
    if (hadc == &hadc1) {
        uint32_t raw_val = adcBuffer[0] & 0xFFF;  // 获取最新值
        Stress_voltage = raw_val * 3.3f / 4095.0f;
        // 在这里处理电压值（例如发送到串口或触发逻辑）
    }
}

