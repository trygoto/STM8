

/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************
 * 文件名  ：led.c
 * 描述    ：IO口配置函数库   
 * 实验平台：iCreate STM8开发板
 * 库版本  ：V2.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20

  iCreate STM8开发板硬件连接
    |--------------------|
    |  LED1-PC7         |
    |--------------------|

****************************************************************************************/

#include "led.h"

void LED_Init(void)
{
   GPIO_Init(GPIOD,GPIO_PIN_7,GPIO_MODE_OUT_PP_HIGH_FAST );//定义LED的管脚的模式
   
}




/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/