/*
 * @Author: 星必尘Sguan
 * @Date: 2025-04-17 15:44:34
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-06-08 20:32:26
 * @FilePath: \demo_STM32F407code\Hardware\esp.c
 * @Description: 实现esp8266_01s连接OneNET物联网模型;
 * @Key_GPIO: PA2 -> USART2_TX; PA3 -> UASRT2_RX;
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "esp.h"

extern UART_HandleTypeDef huart2;

/**
 * @description: AT指令定义（已添加\r\n）
 * @return {*}
 */
static const char *esp_ATmain = "AT\r\n";
static const char *espSet_StationMode = "AT+CWMODE=1\r\n";
static const char *espStart_DHCP = "AT+CWDHCP=1,1\r\n";
// static const char *espConnet_Wifi = "AT+CWJAP=\"星必尘Sguan\",\"sguan12345\"\r\n";
static const char *espSet_Token = "AT+MQTTUSERCFG=0,1,\"d1\",\"REc53ZzF42\",\"version=2018-10-31&res=products%2FREc53ZzF42%2Fdevices%2Fd1&et=1890079256&method=md5&sign=T%2FpNtLjJbXU6BjSW1apFdQ%3D%3D\",0,0,\"\"\r\n";
static const char *espSet_SeverStation = "AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n";
static const char *espReply_Topic = "AT+MQTTSUB=0,\"$sys/REc53ZzF42/d1/thing/property/post/reply\",1\r\n";
static const char *espSet_Topic = "AT+MQTTSUB=0,\"$sys/REc53ZzF42/d1/thing/property/set\",0\r\n";


/**
 * @description: 函数封装ESP8266串口发送信息的功能，简化工作流程;
 * @param {uint8_t} *Str
 * @return {*}
 */
static void ESP_SendString(const char *Str)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)Str, strlen(Str), HAL_MAX_DELAY);
    // HAL_Delay(100);   //适当延时，确保模块的初始化工作正常进行
}


/**
 * @brief 初始化ESP8266并连接MQTT
 * @return Esp_OK: 成功, Esp_ERROR: 失败
 */
Esp_StatusTypeDef ESP_Init(void) {
    // HAL_GPIO_WritePin(Esp_EN_Port, Esp_EN, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(Esp_RST_Port, Esp_RST, GPIO_PIN_SET);
    // 依次发送AT指令并检查响应
	  HAL_Delay(4000);
    ESP_SendString(esp_ATmain);
    HAL_Delay(100);
    ESP_SendString(espSet_StationMode);
    HAL_Delay(100);
    ESP_SendString(espStart_DHCP);
    HAL_Delay(100);
    // ESP_SendString(espConnet_Wifi);
    // HAL_Delay(6000);
    ESP_SendString(espSet_Token);
    HAL_Delay(200);
    ESP_SendString(espSet_SeverStation);
    HAL_Delay(5000);
    ESP_SendString(espReply_Topic);
    HAL_Delay(200);
    ESP_SendString(espSet_Topic);
    return Esp_OK; // 检查所有指令是否均返回OK
}







