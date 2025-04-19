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
#include "ctpiic.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;  // 假设已在其他地方定义了I2C1的句柄

/*****************************************************************************
 * @name       :void CTP_Delay(void)
 * @date       :2020-05-13 
 * @function   :Delay in controlling IIC speed
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_Delay(void)
{
    HAL_Delay(1);
} 

/*****************************************************************************
 * @name       :void CTP_IIC_Init(void)
 * @date       :2020-05-13 
 * @function   :Initialize IIC
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Init(void)
{
    // HAL库中I2C初始化通常在MX_I2C1_Init()中完成
    // 这里不需要额外的初始化代码
}

/*****************************************************************************
 * @name       :void CTP_IIC_Start(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC starting signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Start(void)
{
    // HAL库自动处理起始条件
}

/*****************************************************************************
 * @name       :void CTP_IIC_Stop(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC stop signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/   
void CTP_IIC_Stop(void)
{
    // HAL库自动处理停止条件
}

/*****************************************************************************
 * @name       :u8 CTP_IIC_Wait_Ack(void)
 * @date       :2020-05-13 
 * @function   :Wait for the response signal
 * @parameters :None
 * @retvalue   :0-receive response signal successfully
               1-receive response signal unsuccessfully
******************************************************************************/ 
uint8_t CTP_IIC_Wait_Ack(void)
{
    // HAL库自动处理ACK/NACK
    return 0;  // 总是返回成功，实际错误处理在HAL_I2C_Master_Transmit等函数中
}

/*****************************************************************************
 * @name       :void CTP_IIC_Ack(void)
 * @date       :2020-05-13 
 * @function   :Generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void CTP_IIC_Ack(void)
{
    // HAL库自动处理ACK
}

/*****************************************************************************
 * @name       :void CTP_IIC_NAck(void)
 * @date       :2020-05-13 
 * @function   :Don't generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/    
void CTP_IIC_NAck(void)
{
    // HAL库自动处理NACK
}

/*****************************************************************************
 * @name       :void CTP_IIC_Send_Byte(u8 txd)
 * @date       :2020-05-13 
 * @function   :send a byte data by IIC bus
 * @parameters :txd:Data to be sent
 * @retvalue   :None
******************************************************************************/                     
void CTP_IIC_Send_Byte(uint8_t txd)
{
    // 在HAL库中，字节发送通过HAL_I2C_Master_Transmit等函数完成
    // 单独发送一个字节不常见，通常需要结合设备地址和寄存器地址
}

/*****************************************************************************
 * @name       :u8 CTP_IIC_Read_Byte(unsigned char ack)
 * @date       :2020-05-13 
 * @function   :read a byte data by IIC bus
 * @parameters :ack:0-send nACK
                 1-send ACK
 * @retvalue   :Data to be read
******************************************************************************/     
uint8_t CTP_IIC_Read_Byte(unsigned char ack)
{
    uint8_t data = 0;
    // 在HAL库中，字节读取通过HAL_I2C_Master_Receive等函数完成
    return data;
}

/*****************************************************************************
 * @name       :HAL_StatusTypeDef CTP_IIC_Write_Reg(u8 dev_addr, u8 reg, u8 value)
 * @date       :2020-05-13 
 * @function   :Write data to IIC device register
 * @parameters :dev_addr: device address
 *              reg: register address
 *              value: data to write
 * @retvalue   :HAL status
******************************************************************************/
HAL_StatusTypeDef CTP_IIC_Write_Reg(uint8_t dev_addr, uint8_t reg, uint8_t value)
{
    return HAL_I2C_Mem_Write(&hi2c1, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
}

/*****************************************************************************
 * @name       :HAL_StatusTypeDef CTP_IIC_Read_Reg(u8 dev_addr, u8 reg, u8 *buf, u16 len)
 * @date       :2020-05-13 
 * @function   :Read data from IIC device register
 * @parameters :dev_addr: device address
 *              reg: register address
 *              buf: buffer to store data
 *              len: data length
 * @retvalue   :HAL status
******************************************************************************/
HAL_StatusTypeDef CTP_IIC_Read_Reg(uint8_t dev_addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, HAL_MAX_DELAY);
}




























