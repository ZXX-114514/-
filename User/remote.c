#include "remote.h"
#include "usart.h"
#include "dma.h"
uint8_t dbus_buf[18];
RC rc_ctrl = {0};
mouse mouse_ctrl = {0};
key key_ctrl = {0};
void Remote_Init(void)
{
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dbus_buf, 18);
}
void Remote_Decode(void)
{
    uint16_t byte5 = dbus_buf[5];
    rc_ctrl.ch0 = ((dbus_buf[0] | (dbus_buf[1] << 8)) & 0x07FF);
    rc_ctrl.ch1 = (((dbus_buf[1] >> 3) | (dbus_buf[2] << 5)) & 0x07FF);
    rc_ctrl.ch2 = (((dbus_buf[2] >> 6) | ( dbus_buf[3] << 2) | (dbus_buf[4] << 10)) & 0x07FF);
    rc_ctrl.ch3 = (((dbus_buf[4] >> 1) | (dbus_buf[5] << 7)) & 0x07FF);
    rc_ctrl.s1 = (byte5 >> 4) & 0x03;
    rc_ctrl.s2 = (byte5 >> 6) & 0x03;
    mouse_ctrl.x = ((int16_t)dbus_buf[6]) | ((int16_t)dbus_buf[7] << 8);
    mouse_ctrl.y = ((int16_t)dbus_buf[8]) | ((int16_t)dbus_buf[9] << 8);
    mouse_ctrl.z = ((int16_t)dbus_buf[10]) | ((int16_t)dbus_buf[11] << 8);
    mouse_ctrl.press_l = dbus_buf[12];
    mouse_ctrl.press_r = dbus_buf[13];
    key_ctrl.v = ((dbus_buf[14] | (dbus_buf[15] << 8)) & 0xFFFF);
		rc_ctrl.ch0 -= 1024;
    rc_ctrl.ch1 -= 1024;
    rc_ctrl.ch2 -= 1024;
    rc_ctrl.ch3 -= 1024;
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART3) {
        Remote_Decode();
	  		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, dbus_buf, 18);
    }
}
