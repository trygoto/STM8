#ifndef  __UART2_H
#define  __UART2_H

#include "stm8s.h"




void UART2Init(unsigned int baudrate);

void UART2_SendString(u8* Data,u16 len);

u8 BCC(u8 *p, u8 num); //求异或和



#endif