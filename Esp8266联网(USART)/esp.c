/*
 * @Author: 星必尘Sguan
 * @Date: 2025-04-17 15:44:34
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-04-17 18:43:22
 * @FilePath: \test_esp8266MQTT\Hardware\esp.c
 * @Description: 
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "esp.h"


extern UART_HandleTypeDef huart1;

// AT指令定义（已添加\r\n）
static const char *esp_ATmain = "AT\r\n";
static const char *espSet_StationMode = "AT+CWMODE=1\r\n";
static const char *espStart_DHCP = "AT+CWDHCP=1,1\r\n";
static const char *espConnet_Wifi = "AT+CWJAP=\"星必尘Sguan\",\"sguan12345\"\r\n";
static const char *espSet_Token = "AT+MQTTUSERCFG=0,1,\"d1\",\"REc53ZzF42\",\"version=2018-10-31&res=products%2FREc53ZzF42%2Fdevices%2Fd1&et=1890079256&method=md5&sign=T%2FpNtLjJbXU6BjSW1apFdQ%3D%3D\",0,0,\"\"\r\n";
static const char *espSet_SeverStation = "AT+MQTTCONN=0,\"mqtts.heclouds.com\",1883,1\r\n";
static const char *espReply_Topic = "AT+MQTTSUB=0,\"$sys/REc53ZzF42/d1/thing/property/post/reply\",1\r\n";
static const char *espSet_Topic = "AT+MQTTSUB=0,\"$sys/REc53ZzF42/d1/thing/property/set\",0\r\n";



/**
 * @brief 初始化ESP8266并连接MQTT
 * @return Esp_OK: 成功, Esp_ERROR: 失败
 */
Esp_StatusTypeDef Esp_Init(void) {
    HAL_GPIO_WritePin(Esp_EN_Port, Esp_EN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Esp_RST_Port, Esp_RST, GPIO_PIN_SET);
    // 依次发送AT指令并检查响应
    HAL_UART_Transmit(&huart1,(uint8_t *)esp_ATmain,strlen(esp_ATmain),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)esp_ATmain,strlen(esp_ATmain),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_StationMode,strlen(espSet_StationMode),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_StationMode,strlen(espSet_StationMode),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espStart_DHCP,strlen(espStart_DHCP),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espStart_DHCP,strlen(espStart_DHCP),HAL_MAX_DELAY);
    HAL_Delay(100);
    // HAL_UART_Transmit(&huart1,(uint8_t *)espConnet_Wifi,strlen(espConnet_Wifi),HAL_MAX_DELAY);
    // HAL_Delay(6000);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_Token,strlen(espSet_Token),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_Token,strlen(espSet_Token),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_SeverStation,strlen(espSet_SeverStation),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_SeverStation,strlen(espSet_SeverStation),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espReply_Topic,strlen(espReply_Topic),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espReply_Topic,strlen(espReply_Topic),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_Topic,strlen(espSet_Topic),HAL_MAX_DELAY);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1,(uint8_t *)espSet_Topic,strlen(espSet_Topic),HAL_MAX_DELAY);
    HAL_Delay(100);
    return Esp_OK; // 检查所有指令是否均返回OK
}







