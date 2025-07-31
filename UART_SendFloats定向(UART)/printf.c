/*
 * @Author: 星必尘Sguan
 * @Date: 2025-05-26 15:32:26
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-07-17 22:36:15
 * @FilePath: \demo_STM32F407code\Hardware\printf.c
 * @Description: 使用USART串口收发和数据处理
 * @Key_GPIO: Many;
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "printf.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "BlueTooth.h"
#include "Asppro.h"

extern UART_HandleTypeDef huart1;  // 确保已在 main.c 定义 UART_HandleTypeDef huart
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;

/**
 * @description: 接收串口消息的数组;
 * MX_USART1  STM32F407与电脑传输数据/有线控制电控
 * MX_USART2  与ESP8266_01s模块通信，实现联网OneNET云平台
 * MX_USART3  海凌科24G毫米波模块通信，人体存在传感
 * MX_UART4   和天问语音Module的通信
 * MX_USART6  蓝牙模块串口通信
 * @return {*}
 */
//串口1控制电控板的全局变量
uint8_t G431_Buffer[10];
//串口2控制esp模块的变量
uint8_t esp_readBuffer[esp_BUFFER_SIZE];
volatile bool rx_complete = false;
//串口3读取海凌科模块
uint8_t HLK24G_readBuffer[10];
uint8_t H750_readBuffer[10];
//串口4控制语音模块
uint8_t Asppro_readBuffer[10];
//串口6蓝牙连接读写Buffer
uint8_t BlueTooth_readBuffer[10];


/**
 * @brief 通过 UART2 发送多个 float 数据
 * @param data float 数组指针
 * @param count 数据个数
 * @param decimal_places 小数位数（如 2 表示保留 2 位小数）
 */
void UART_SendFloats(float *data, uint8_t count, uint8_t decimal_places) {
    char buffer[128];  // 缓冲区（根据数据量调整大小）
    char *ptr = buffer;  // 指针指向缓冲区起始位置
    // 遍历所有 float 数据
    for (uint8_t i = 0; i < count; i++) {
        // 格式化 float 到字符串（如 "1.23"）
        ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), 
                      "%.*f", decimal_places, data[i]);
        // 添加逗号分隔（最后一个数据不加）
        if (i < count - 1) {
            ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), ", ");
        }
    }
    ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), "\n");    // 添加换行符
    // 通过 HAL_UART_Transmit 发送
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, ptr - buffer, HAL_MAX_DELAY);
}


/**
 * @description: 不定长数据接收完成回调函数
 * @param {UART_HandleTypeDef} *huart
 * @param {uint16_t} Size
 * @return {*}
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART1) {
        // 重新启动接收，使用Ex函数，接收不定长数据
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, G431_Buffer, sizeof(G431_Buffer));
        // 关闭DMA传输过半中断（HAL库默认开启，但我们只需要接收完成中断）
        __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
    }
    if (huart->Instance == USART2) {
        rx_complete = true;
    }
    if (huart->Instance == USART3) {
        for(uint16_t i = 0; i < sizeof(H750_readBuffer); i++) {
            // 遇到结束符停止检查
            if(H750_readBuffer[i] == '\0' || H750_readBuffer[i] == '\r' || H750_readBuffer[i] == '\n') {
                break;
            }
            // 检查是否是0xB0命令
            if(H750_readBuffer[i] == 0x02) {
                Buzzer_Own(300);
            }
        }
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, H750_readBuffer, sizeof(H750_readBuffer));
        // 关闭DMA传输过半中断（HAL库默认开启，但我们只需要接收完成中断）
        __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);
    }
    if (huart->Instance == UART4) {
        Asppro_Update();
    }
    if (huart->Instance == USART6) {
        BlueTooth_Update();
    }
}

