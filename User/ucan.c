#include "can.h"
#include "main.h"
#include "remote.h"
#define REMOTE_CAN_ID   0x301   /* 遥控器数据发送帧 ID */
void CAN_Filter_Init(void)
{
    CAN_FilterTypeDef filter;
    filter.FilterActivation = ENABLE;
    filter.FilterBank = 14;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO1;
    filter.FilterIdHigh = 0;
    filter.FilterIdLow = 0;
    filter.FilterMaskIdHigh = 0;
    filter.FilterMaskIdLow = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.SlaveStartFilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &filter);
}
void CAN_Start(void)
{
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);
}
void CAN2_Send_Remote(void)
{
    CAN_TxHeaderTypeDef tx_header;
    uint8_t tx_data[8];
    uint32_t tx_mail;
    int16_t ch_pitch = rc_ctrl.ch1; /* ch1 对应 pitch */
    int16_t ch_yaw   = rc_ctrl.ch0; /* ch0 对应 yaw */
    if (ch_pitch < 5 && ch_pitch > -5) ch_pitch = 0;
    if (ch_yaw   < 30 && ch_yaw   > -30) ch_yaw   = 0;
    uint8_t s1 = rc_ctrl.s1;   
    uint8_t s2 = rc_ctrl.s2;
    tx_data[0] = (uint8_t)(ch_pitch & 0xFF); 
    tx_data[1] = (uint8_t)((ch_pitch >> 8) & 0xFF);  
    tx_data[2] = (uint8_t)(ch_yaw & 0xFF);
    tx_data[3] = (uint8_t)((ch_yaw >> 8) & 0xFF);
    tx_data[4] = s1;
    tx_data[5] = s2;
    tx_data[6] = 0; 
    tx_data[7] = 0;
    tx_header.StdId = REMOTE_CAN_ID;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 8;
    tx_header.TransmitGlobalTime = DISABLE;
    HAL_CAN_AddTxMessage(&hcan2, &tx_header, tx_data, &tx_mail);
}
