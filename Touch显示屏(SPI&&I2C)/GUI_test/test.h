/*
 * @Author: 星必尘Sguan
 * @Date: 2025-04-27 22:11:04
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-04-29 21:42:03
 * @FilePath: \test_SPIscreen\GUI\test.h
 * @Description: 
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#ifndef __TEST_H__
#define __TEST_H__

#include "stm32f4xx_hal.h"

void DrawTestPage(uint8_t *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);
void Test_Read(void);
void Test_Dynamic_Num(void);
#endif
