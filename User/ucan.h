#ifndef __UCAN_H
#define __UCAN_H
#include "can.h"

void CAN_Filter_Init(void);
void CAN_Start(void);
void CAN2_Send_Remote(void);
extern uint32_t tx_state;
#endif
