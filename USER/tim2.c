#include "stm8s.h"
#include "tim2.h"

void TIM2_Init()
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_1 ,  //定时器2预分频数为 1 分频，即定时器时钟 = 系统时钟 = 16MHz
                    16000                 //设置1毫秒时间自动重载 16000
                    );
  TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE); //使能定时器2更新中断
  TIM2_ARRPreloadConfig(ENABLE);          //允许自动仲裁
  TIM2_Cmd(ENABLE);        //启动定时器2开始计数
}

