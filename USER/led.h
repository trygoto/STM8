/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************
 * �ļ���  ��led.c
 * ����    ��IO�����ú�����   
 * ʵ��ƽ̨��iCreate STM8������
 * ��汾  ��V2.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20

  iCreate STM8������Ӳ������
    |--------------------|
    |  LED1-PD0          |
    |  LED2-PD1          |
    |  LED3-PD2          |
    |  LED4-PD3          |
    |--------------------|

****************************************************************************************/

#ifndef __LED_H
#define __LED_H
#include "stm8s_gpio.h"

#define ON  0
#define OFF 1
#define LED_ON  GPIO_WriteLow(GPIOD, GPIO_PIN_7);
#define LED_OFF GPIO_WriteHigh(GPIOD, GPIO_PIN_7)
                        
#define LED01 GPIO_WriteReverse(GPIOD, GPIO_PIN_7);

void LED_Init(void);


#endif


/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/