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
/*main---------|中断1----------|按键扫描
                 |                |数码管扫描
                 |
                 |中断2----------|串口接收数据
                 |
                 |
                 |HELL_SHOW----|-菜单1处理操作数据		
                 |                |-菜单2处理操作数据
                                  |-菜单3处理操作数据
                                  |-.........................
/********************************************/
int main(void)
{
  disableInterrupts();    				 //先禁止系统总中断 
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); //内部时钟为1分频 = 16Mhz
  TIM2_Init();							 //1MS中断
  UART2Init(115200);              		 //调用USART2初始化函数
  LED_Init();           				 //调用LED初始化函数
  SW02Init();							 //按键初始化
  KEY_Init(); 							 //旋钮初始化
  seg_Init();							 //数码管初始化
  LED_ON;								 //关闭LED灯		
  enableInterrupts();   				 //使能系统总中断 
  while(1) 
  {
  
    // HELL_SHOW();  					 	 //显示函数
     if (USART_RX_STA&0x8000)
		 {
			UART2_SendString(USART_RX_BUF,USART_RX_STA&0X3FFF);
			USART_RX_STA=0;
		 }
    
  }        
}

