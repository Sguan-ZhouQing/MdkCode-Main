/*
 * @Author: 星必尘Sguan
 * @Date: 2025-05-26 15:32:04
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-07-04 03:23:39
 * @FilePath: \demo_STM32F407code\Hardware\json.c
 * @Description: 实现json数据的接收和解析
 * @Key_GPIO: NULL;
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "json.h"
#include "Buzzer.h"

extern UART_HandleTypeDef huart2;
extern uint8_t esp_readBuffer[esp_BUFFER_SIZE];
extern volatile bool rx_complete;

// 全局变量定义
float temp = 0.0f;                 // AHT20传感器上传的温度（展示用）
float humi = 0.0f;                 // AGT20上传的湿度数据（展示用）
float stress = 0.0f;               // 压力传感器数值（展示用）
float distance = 0.0f;             // 距离传感器，测人与药仓的距离（展示用）
bool power_flag = true;            // 电控板的电源开关（控制）
bool motor_flag = true;            // 电机强制归零开关（控制）
uint32_t timer = 0;                // 单片机获取的时间戳
uint8_t warehouse_left[6] = {0};   // 药仓占用情况左部分（控制）
uint8_t warehouse_right[6] = {0};  // 药仓占用情况右部分（控制）
uint8_t command = 0;               // 存取药的命令0-24（控制）
uint8_t device_ID = 0;             // 用户身份核验

/**
 * @description: 解析MQTT消息，提取JSON部分
 * @param {char} *message MQTT原始消息
 * @return {void}
 */
void parse_mqtt_message(const char *message) {
    // 查找JSON数据的起始位置
    const char *json_start = strchr(message, '{');
    if (json_start == NULL) {
        return; // 没有找到JSON数据
    }
    // 调用JSON解析函数
    parse_json_data(json_start);
}

/**
 * @description: 解析JSON数据并更新全局变量
 * @param {char} *json_str JSON字符串
 * @return {void}
 */
void parse_json_data(const char *json_str) {
    // 解析JSON
    cJSON *root = cJSON_Parse(json_str);
    if (root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            // printf("JSON parse error before: %s\n", error_ptr);
            Buzzer_Control();
        }
        return;
    }
    // 获取params对象
    cJSON *params = cJSON_GetObjectItemCaseSensitive(root, "params");
    if (params == NULL) {
        cJSON_Delete(root);
        return;
    }
    
    // 解析各个字段
    cJSON *item = NULL;
    // 解析command
    item = cJSON_GetObjectItemCaseSensitive(params, "command");
    if (cJSON_IsNumber(item)) {
        command = (uint8_t)item->valueint;
    }
    // 解析power_flag
    item = cJSON_GetObjectItemCaseSensitive(params, "power_flag");
    if (cJSON_IsBool(item)) {
        power_flag = cJSON_IsTrue(item);
    }
    // 解析motor_flag
    item = cJSON_GetObjectItemCaseSensitive(params, "motor_flag");
    if (cJSON_IsBool(item)) {
        motor_flag = cJSON_IsTrue(item);
    }
    // 解析timer
    item = cJSON_GetObjectItemCaseSensitive(params, "timer");
    if (cJSON_IsNumber(item)) {
        timer = (uint32_t)item->valuedouble;
    }
    // 解析device_ID
    item = cJSON_GetObjectItemCaseSensitive(params, "device_ID");
    if (cJSON_IsNumber(item)) {
        device_ID = (uint8_t)item->valueint;
    }
    // 解析warehouse_left数组
    item = cJSON_GetObjectItemCaseSensitive(params, "warehouse_left");
    if (cJSON_IsArray(item)) {
        update_warehouse_left(item);
    }
    // 解析warehouse_right数组
    item = cJSON_GetObjectItemCaseSensitive(params, "warehouse_right");
    if (cJSON_IsArray(item)) {
        update_warehouse_right(item);
    }
    
    // 释放JSON对象
    cJSON_Delete(root);
}

/**
 * @description: 更新warehouse_left数组
 * @param {cJSON} *array JSON数组对象
 * @return {void}
 */
void update_warehouse_left(cJSON *array) {
    int size = cJSON_GetArraySize(array);
    size = (size > 6) ? 6 : size; // 确保不超过数组大小
    
    for (int i = 0; i < size; i++) {
        cJSON *item = cJSON_GetArrayItem(array, i);
        if (cJSON_IsNumber(item)) {
            warehouse_left[i] = (uint8_t)item->valueint;
        }
    }
}

/**
 * @description: 更新warehouse_right数组
 * @param {cJSON} *array JSON数组对象
 * @return {void}
 */
void update_warehouse_right(cJSON *array) {
    int size = cJSON_GetArraySize(array);
    size = (size > 6) ? 6 : size; // 确保不超过数组大小
    
    for (int i = 0; i < size; i++) {
        cJSON *item = cJSON_GetArrayItem(array, i);
        if (cJSON_IsNumber(item)) {
            warehouse_right[i] = (uint8_t)item->valueint;
        }
    }
}


// 在主循环中处理
void Json_ProcessData_tick(void) {
    if (rx_complete) {
        // 查找JSON起始位置（跳过"+MQTTSUBRECV..."前缀）
        char *json_start = strchr((char*)esp_readBuffer, '{');
        if (json_start) {
            parse_json_data(json_start);
        }
        // 准备下一次接收
        rx_complete = false;
        memset(esp_readBuffer, 0, esp_BUFFER_SIZE);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart2, esp_readBuffer, sizeof(esp_readBuffer));
        __HAL_DMA_DISABLE_IT(huart2.hdmarx, DMA_IT_HT);
    }
}
