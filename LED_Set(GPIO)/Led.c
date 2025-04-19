/*
 * @Author: 星必尘Sguan
 * @Date: 2025-03-30 16:56:59
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-03-30 17:23:59
 * @FilePath: \demo_myATH20\Hardware\Led.c
 * @Description: 
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "LED.h"

LED_INFO led_info = {0};


/**
 * @description: PC13口的led灯开关
 * @param {_Bool} status
 * @return {*}
 */
void Led_Set(_Bool status)
{
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,status == LED_ON ? GPIO_PIN_RESET:GPIO_PIN_SET);
	
	led_info.Led_Status = status;

}
