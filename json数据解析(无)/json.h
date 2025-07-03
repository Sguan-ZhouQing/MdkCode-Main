#ifndef __JSON_H
#define __JSON_H

#include "printf.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "cJSON.h"

// 全局变量声明
extern float temp;
extern float humi;
extern float stress;
extern float distance;
extern bool power_flag;
extern bool motor_flag;
extern uint32_t timer;
extern uint8_t warehouse_left[6];
extern uint8_t warehouse_right[6];
extern uint8_t command;
extern uint8_t device_ID;

// 函数声明
void parse_mqtt_message(const char *message);
void parse_json_data(const char *json_str);
void update_warehouse_left(cJSON *array);
void update_warehouse_right(cJSON *array);
void Json_ProcessData_tick(void);

#endif // JSON_H
