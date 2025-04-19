//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F407ZGT6,正点原子Explorer STM32F4开发板,主频168MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/08/09
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接        DC5V/3.3V      //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为SPI总线
//     LCD模块                STM32单片机    
//    SDI(MOSI)      接          PB5          //液晶屏SPI总线数据写信号
//    SDO(MISO)      接          PB4          //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机 
//       LED         接          PB13         //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
//       SCK         接          PB3          //液晶屏SPI总线时钟信号
//     LCD_RS        接          PB14         //液晶屏数据/命令控制信号
//     LCD_RST       接          PB12         //液晶屏复位控制信号
//     LCD_CS        接          PB15         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                STM32单片机 
//     CTP_INT       接          PB1          //电容触摸屏中断信号
//     CTP_SDA       接          PF11         //电容触摸屏IIC数据信号
//     CTP_RST       接          PC5          //电容触摸屏复位信号
//     CTP_SCL       接          PB0          //电容触摸屏IIC时钟信号
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/
#include "mySPI.h"

extern SPI_HandleTypeDef hspi1;  // SPI1句柄

/*****************************************************************************
 * @name       :u8 SPI_WriteByte(SPI_TypeDef* SPIx, u8 Byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :SPIx: SPI类型(实际使用hspi1句柄)
                Byte:要写入的数据
 * @retvalue   :总线接收到的数据
******************************************************************************/
uint8_t SPI_WriteByte(SPI_HandleTypeDef* SPIx, uint8_t Byte)
{
    uint8_t received = 0;
    HAL_SPI_TransmitReceive(&hspi1, &Byte, &received, 1, HAL_MAX_DELAY);
    return received;
}

/*****************************************************************************
 * @name       :void SPI_SetSpeed(SPI_TypeDef* SPIx, u8 SpeedSet)
 * @date       :2018-08-09 
 * @function   :设置硬件SPI速度
 * @parameters :SPIx: SPI类型(实际使用hspi1句柄)
                SpeedSet:0-高速
                         1-低速
 * @retvalue   :None
******************************************************************************/
void SPI_SetSpeed(SPI_HandleTypeDef* SPIx, uint8_t SpeedSet)
{
    hspi1.Instance->CR1 &= ~SPI_CR1_BR;  // 清除预分频位
    
    if(SpeedSet == 1) // 高速
    {
        hspi1.Instance->CR1 |= SPI_BAUDRATEPRESCALER_2;  // Fpclk/2
    }
    else // 低速
    {
        hspi1.Instance->CR1 |= SPI_BAUDRATEPRESCALER_16; // Fpclk/16
    }
    
    __HAL_SPI_ENABLE(&hspi1);  // 使能SPI
}

/*****************************************************************************
 * @name       :void SPI1_Init(void)    
 * @date       :2018-08-09 
 * @function   :初始化STM32硬件SPI1
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void SPI1_Init(void)    
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 1. 使能时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();
    
    // 2. 配置GPIO
    // PB3(SCK), PB4(MISO), PB5(MOSI)
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // 3. 配置SPI
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        // 初始化错误处理
        while(1);
    }
    
    // 4. 使能SPI
    __HAL_SPI_ENABLE(&hspi1);
}
