#include"stm8s.h"
#include "UART2.h"
/*******************************************************************************
**函数名称：void UART1Init(unsigned int baudrate)
**功能描述：初始化USART模块
**入口参数：unsigned int baudrate  -> 设置串口波特�?
**输出：无
*******************************************************************************/
void UART2Init(unsigned int baudrate)
{   
    UART2_Init(baudrate ,            //配置通讯波特�?
               UART2_WORDLENGTH_8D , //配置8位宽�?
               UART2_STOPBITS_1 ,    //配置1位停止位
               UART2_PARITY_NO ,     //配置无校�?
               UART2_SYNCMODE_CLOCK_DISABLE , //
               UART2_MODE_TXRX_ENABLE //设置USART1发送和接收模式
               );
    
    UART2_ITConfig(UART2_IT_RXNE , ENABLE);   //使能接收中断
    UART2_Cmd(ENABLE);    //使能USART2
}
void UART2_SendByte(u8 data)
{
    UART2_SendData8((unsigned char)data);
  /* Loop until the end of transmission */
  while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);
}

void UART2_SendString(u8* Data,u16 len)
{
  u16 i=0;
  for(;i<len;i++)
    UART2_SendByte(Data[i]);
  
}

u8 BCC(u8 *p, u8 num) //求异或和
{
  u8 i;
  u8 temp = 0;
  for(i = 0; i < num; i++)
  {
    temp ^= p[i];
  }
  return temp;
}
