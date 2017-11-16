#include "stm8s.h"
#include "tim2.h"
#include "seg.h"
#include "led.h"
#include "key_scan.h"
#include "task.h"
#include "UART2.h"
#include "RS232command.h"

extern u8 USART_RX_BUF[]; 
extern u8 flag_232_rx;
extern u8 js;
extern u16 Pmode;
extern int command_flag;
extern int OK_flag;
int command21_flag=0;
 extern u16 USART_RX_STA;
/********************************************/
/*main---------|�ж�1----------|����ɨ��
                 |                |�����ɨ��
                 |
                 |�ж�2----------|���ڽ�������
                 |
                 |
                 |HELL_SHOW----|-�˵�1�����������		
                 |                |-�˵�2�����������
                                  |-�˵�3�����������
                                  |-.........................
/********************************************/
int main(void)
{
  disableInterrupts();    				 //�Ƚ�ֹϵͳ���ж� 
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); //�ڲ�ʱ��Ϊ1��Ƶ = 16Mhz
  TIM2_Init();							 //1MS�ж�
  UART2Init(115200);              		 //����USART2��ʼ������
  LED_Init();           				 //����LED��ʼ������
  SW02Init();							 //������ʼ��
  KEY_Init(); 							 //��ť��ʼ��
  seg_Init();							 //����ܳ�ʼ��
  LED_ON;								 //�ر�LED��		
  enableInterrupts();   				 //ʹ��ϵͳ���ж� 
  while(1) 
  {
  
    // HELL_SHOW();  					 	 //��ʾ����
     if (USART_RX_STA&0x8000)
		 {
			UART2_SendString(USART_RX_BUF,USART_RX_STA&0X3FFF);
			USART_RX_STA=0;
		 }
    
  }        
}

