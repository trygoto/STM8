#include "stm8s.h"
#include "tim2.h"

void TIM2_Init()
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,  //��ʱ��2Ԥ��Ƶ��Ϊ 1 ��Ƶ������ʱ��ʱ�� = ϵͳʱ�� = 16MHz
                    16000                 //����1����ʱ���Զ����� 16000
                    );
  TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE); //ʹ�ܶ�ʱ��2�����ж�
  TIM2_ARRPreloadConfig(ENABLE);          //�����Զ��ٲ�
  TIM2_Cmd(ENABLE);        //������ʱ��2��ʼ����
}

