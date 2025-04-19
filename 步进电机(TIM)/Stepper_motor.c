/*
 * @Author: 星必尘Sguan
 * @Date: 2025-04-10 19:00:48
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-04-11 12:43:17
 * @FilePath: \tset_StepperMotor\Hardware\Stepper_motor.c
 * @Description: stm32使用HAL库驱动步进电机;
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */

#include "Stepper_motor.h"
#include <stdlib.h>  // 包含 abs() 函数的头文件
#include "tim.h"

#define Motor_DIR GPIO_PIN_11
#define Motor_DIR_Port GPIOB
#define Motor_Speed GPIO_PIN_10
#define Motor_Speed_Port GPIOB

static uint32_t temp;
static uint32_t freq_count;
static int32_t Step_count;


/**
 * @description: 设置转速百分比,Step为NULL则不设置具体步数;
 * @param {int32_t} Velocity 速度大小设置(包含正负)
 * @param {void} Step 给定具体转动步数
 * @return {*}
 */
void StepperMotor_Contrl(int32_t Velocity,int32_t Step)
{
    //需要设置10us定时中断一次
    __disable_irq();  // 关闭中断
    HAL_GPIO_WritePin(Motor_DIR_Port, Motor_DIR, (Velocity > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    temp = (uint32_t)abs(Velocity);
    if (Step != 0){
        Step_count = (int32_t)Step;
    }
    else{
        Step_count = -1;
    }
    __enable_irq();   // 重新启用中断
}

/**
 * @description: TIM1的回调函数;
 * @param {TIM_HandleTypeDef} *htim
 * @return {*}
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1 && temp != 0)  // 检查是否是 TIM1 触发的中断
    {
        if (Step_count == -1)
        {
            freq_count += 1;
            // 在这里写你的定时任务代码
            if (freq_count == 10000/temp){
                HAL_GPIO_TogglePin(Motor_Speed_Port,Motor_Speed);
                freq_count = 0;
            }
        }
        else if(Step_count != 0)
        {
            freq_count += 1;
            // 在这里写你的定时任务代码
            if (freq_count == 10000/temp){
                HAL_GPIO_TogglePin(Motor_Speed_Port,Motor_Speed);
                freq_count = 0;
                Step_count--;
            }
        }
    }
}
