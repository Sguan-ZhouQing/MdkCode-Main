/*
 * @Author: 星必尘Sguan
 * @Date: 2025-10-30 20:39:20
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-10-30 21:08:00
 * @FilePath: \stm_CANcode\Hardware\SguanCAN.c
 * @Description: CAN总线通讯实现
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "SguanCAN.h"

extern CAN_HandleTypeDef hcan;
uint8_t SguanCAN_RxFlag;
CAN_RxHeaderTypeDef RxMsg;
uint8_t RxMsgData[4];

/**
 * @description: CAN过滤器初始化
 * @return {*}
 */
HAL_StatusTypeDef SguanCAN_FilterInit(void) {
    CAN_FilterTypeDef CAN_FilterInitStructure;
    CAN_FilterInitStructure.FilterBank=0;//指定需要初始化的过滤器，过滤器总共有13个
    CAN_FilterInitStructure.FilterScale=CAN_FILTERSCALE_32BIT;
    CAN_FilterInitStructure.FilterMode=CAN_FILTERMODE_IDMASK;
    CAN_FilterInitStructure.FilterFIFOAssignment=CAN_FILTER_FIFO0;
    CAN_FilterInitStructure.FilterIdHigh=0x0000;
    CAN_FilterInitStructure.FilterIdLow=0x0000;
    CAN_FilterInitStructure.FilterMaskIdHigh=0x0000;
    CAN_FilterInitStructure.FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.FilterActivation=CAN_FILTER_ENABLE;
    return HAL_CAN_ConfigFilter(&hcan, &CAN_FilterInitStructure);
}

/**
 * @description: 发送CAN字节信息
 * @param {uint32_t} ID
 * @param {uint8_t} Length
 * @param {uint8_t} *Data
 * @return {*}
 */
HAL_StatusTypeDef SguanCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data) {
    CAN_TxHeaderTypeDef TxMessage;
    TxMessage.StdId = ID;//需发送消息的报文标准格式ID
    TxMessage.ExtId = ID;//需发送消息的报文扩展格式ID
    TxMessage.IDE = CAN_ID_STD;//需发送消息的报文类型,假如此处选择标准格式
    // CAN_Id_Standard则ExtId参数无效;假如此处选择扩展格式CAN_Id_Extended则StdId无效
    TxMessage.RTR = CAN_RTR_DATA;//设置需要发送的是数据帧
    TxMessage.DLC = Length;//发送报文的长度
    uint32_t pTxMailbox;
    return HAL_CAN_AddTxMessage(&hcan,&TxMessage,Data,&pTxMailbox);
}

/**
 * @description: CAN接收Flag
 * @return {*}
 */
uint8_t SguanCAN_ReceiveFlag(void) {
    //由于前面配置过滤器时通过过滤器的报文进入FIFO0队列，且这个程序设置成了环回模式，自发自收。
    //所以发出的报文必会存入自身的FIFO0队列中
    uint32_t aaa=HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0);
    if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0) > 0) {
        return 1;
    }
    return 0;
}


//从FIFO0中读出数据
void SguanCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data) {
    CAN_RxHeaderTypeDef RxMessage;
    HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &RxMessage,Data);//从FIFO0中读出数据
    if (RxMessage.IDE == CAN_ID_STD){ //判断读出的数据的ID类型
        *ID = RxMessage.StdId;
    }
    else{
        *ID = RxMessage.ExtId;
    }
    if (RxMessage.RTR == CAN_RTR_DATA){ //判断读出的数据时数据帧还是遥控帧
        //数据帧处理
        *Length = RxMessage.DLC;
    }
    else{
        //遥控帧处理
    }
}

//在stm32f1xx_it.c中的中断函数USB_LP_CAN1_RX0_IRQHandler转到定义后找到以下回调函数
//替换SguanCAN_Receive()和SguanCAN_ReceiveFlag()函数
//主函数调用“__HAL_CAN_ENABLE_IT(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);”
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if( HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &RxMsg, RxMsgData)==HAL_OK){
        SguanCAN_RxFlag=1;
    }
}
