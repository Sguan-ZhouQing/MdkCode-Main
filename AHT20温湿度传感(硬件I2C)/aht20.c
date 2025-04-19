/*
 * @Author: 星必尘Sguan
 * @Date: 2025-03-30 12:28:26
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-03-30 13:10:56
 * @FilePath: \demo_myATH20\Hardware\ath20.c
 * @Description: 
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "aht20.h"

#define AHT20_ADDRESS 0x70
//这里定义从机地址，由于AHT20从机为0x38。
//因为这个AHT20 ，从机地址为7位，所以需要左移一位，变成8位。
//所以，0x38，左移一位后，变成了0x70


void AHT20_Int()
{
	uint8_t readBuffer;//用来存放，AHT20工作状态是否正常的数据。是否为0x38
	HAL_Delay(50);//由于模块启动，需要等待40ms
	HAL_I2C_Master_Receive(&hi2c2, AHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
	//&&hi2c1,表示需要操作的i2c的端口。
	//AHT20_ADDRESS,表示需要操作的从机地址。因为是读取数据，这个函数，会将AHT20——ADDRESS变成0x71
	//&readBuffer,读取到的数据，需要放的地方。
	//1,表示，需要读取1位数据
	// HAL_MAX_DELAY,一直等待下去，直到接收完成。


	if((readBuffer & 0x08)==0x00)	//判断，AHT20，bit[3]是否为1。不为1，就进入程序进行初始化。
	{
		uint8_t sendBuffer[3]={0xBE,0x08,0x00};//需要定义这个数组，存放，初始化的数据。
		HAL_I2C_Master_Transmit(&hi2c2, AHT20_ADDRESS, sendBuffer,3, HAL_MAX_DELAY);
		//&&hi2c1,表示需要操作的i2c的端口。
		//AHT20_ADDRESS,表示需要操作的从机地址。
		//sendBuffe,需要发送的数据，读取到的数据，需要放的地方。
		//3,表示，需要发送3位数据
		// HAL_MAX_DELAY,一直等待下去，直到发送完成。
	}

}


void AHT20_Red(float *Temperature , float *Humidity)
{
	uint8_t sendBuffer[3]={0xAC,0x33,0x00};
	uint8_t readBuffer[6];

	HAL_I2C_Master_Transmit(&hi2c2, AHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
	//&hi2c1,需要操作I2c的设备
	// AHT20_ADDRESS.温度传感器的I2C地址
	//sendBuffer,需要发送的指令（发送后就可以获得数据）
	// 3,需要发送的数据长度
	//HAL_MAX_DELAY,一直等待发送完成
	HAL_Delay(100);//--------AHT20 接收到信息后，需要等待100ms，让其完成测量

	HAL_I2C_Master_Receive(&hi2c2, AHT20_ADDRESS, readBuffer, 6, HAL_MAX_DELAY);
	//&hi2c1.获取这个接口的数据。
	//AHT20_ADDRESS，需要获取的从机地址。
	//readBuffer,需要保存到的地址。
	//6,需要保存的数据长度。
	//HAL_MAX_DELAY,一直等待6个数据，保存完成。


	if((readBuffer[0] & 0x80)==0x00)
	{
		uint32_t data=0;
		data=((uint32_t)readBuffer[3]>>4)+((uint32_t)readBuffer[2]<<4)+((uint32_t)readBuffer[1]<<12);
		*Humidity = data * 100.0f / (1<<20);

		data=(((uint32_t)readBuffer[3]& 0xf)<<16)+((uint32_t)readBuffer[4]<<8)+(uint32_t)readBuffer[5];
		*Temperature=data * 200.0f/(1<<20)-50;

	}
}

