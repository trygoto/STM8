/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************
 * 文件名  ：key_scan.c
 * 描述    ：按键配置函数库   
 * 实验平台：iCreate STM8开发板
 * 库版本  ：V2.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20
  
****************************************************************************************/
#include "key_scan.h"
#include "stm8s_gpio.h"
#include "tim2.h"
#include "seg.h"

 char addflag=0,decflag=0;



u16 add_count,dec_count;
u8 add_flag=0,dec_flag=0;
u16 keyadd_count,keydec_count;

u8 key=0;
u8 short_key=0;
u8 double_key=0;
u8 long_key=0;
void KEY_Init(void)
{
 //   GPIO_Init(GPIOE,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);//PC6   SW02
   
    GPIO_Init(GPIOA,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT); //PA3  SW01 A
    
    GPIO_Init(GPIOA,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);//PF4   SW01 B    
   
}

void SW02Init()
{
  //GPC->PIN6 设置端口PE->5的输入输出方向寄存器为输入方向 , 上拉电阻输入 , 使能外部中断
  GPIO_Init(GPIOE , GPIO_PIN_5 , GPIO_MODE_IN_PU_IT);  
  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE , EXTI_SENSITIVITY_FALL_ONLY); //PC端口为下降沿触发中断
}


void CodingsWitchPollint()
{
		static uchar Aold,Bold;
		static uchar st=0;
		
	
	if( CodingsWitch_A&& CodingsWitch_B)  st=1;
	
	if(st)
	{
			if( CodingsWitch_A==0&& CodingsWitch_B==0)
			{
                                if(Aold)//旋钮增加
				{
                                        st=0;
                                        add_flag=1;
                                        dec_flag=0; 
                                        
                                      } 
                                
				if(Bold)   				//旋钮减小
				{
					st=0;                                  
                                        add_flag=0;
                                        dec_flag=1;
				}
			}
	}
	Aold=CodingsWitch_A;
	Bold=CodingsWitch_B;
     
	
}



unsigned char key_driver(void)  
{  
    static unsigned char key_state = key_state_0, key_time = 0;  
    unsigned char key_press, key_return = N_key;  

    key_press = SW02 ;                    // 读取IO电平

    switch (key_state)  
    {  
      	case key_state_0:                              // 按键初始态
        if (!key_press) key_state = key_state_1;      //按键被按下，状态转换到消抖和确认状态 
        break;  
        
      	case key_state_1:                      //按键消抖与确认态
        if (!key_press)  
        {  
             key_time = 0;                   //   
             key_state = key_state_2;   // 按键仍然被按下，消抖完成，状态转换到按下键时间的计时状态，但返回的还是无键事件  
        }  
        else  
             key_state = key_state_0;   //按键已抬起，转换到按键初始态。此处完成和实现软件消抖，其实按键的按下和释放都在此消抖
        break;  
        
      	case key_state_2:  
        if(key_press)  
        {  
             key_return = S_key;        // 此时按键释放，说明是产生一次短操作，回送S_key
             key_state = key_state_0;   // 转换到初始态
        }  
        else if (++key_time >= 20)     //继续按下，计时加10ms（10ms为本函数循环执行间隔）
        {  
             key_return = L_key;        // 按下时间>1000ms,次按键为长按键操作，返回长键事件 
             key_state = key_state_3;   //转换到等待按键释放状态
        }  
        break;  

      	case key_state_3:                 // 等待按键释放状态，此状态只返回无按键事件
        if (key_press) key_state = key_state_0; //按键已释放，转换到按键初始态
        break;  
    }  
    return key_return;  
}

/*********************************************************************************************************
** 函数名称：key_read
** 功能描述：先根据key_driver的状态指示，再根据按键的状态，确定到底是不按，短按，长按，双击，
**
** 输入: key_driver
**
** 输出：无
**         
**全局变量：无

**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
unsigned char key_read(void)  
{  
    static unsigned char key_m = key_state_0, key_time_1 = 0;  
    unsigned char key_return = N_key,key_temp;  
      
    key_temp = key_driver();  
      
    switch(key_m)  
    {  
        	case key_state_0:  
        	if (key_temp == S_key )  
            {  
                 key_time_1 = 0;               //第1次单击，不返回，到下一个状态判断后面是否出现双击
                 key_m = key_state_1;  
            }  
            else  
                 key_return = key_temp;        //对于无键，长键，返回原事件
            break;  

        	case key_state_1:  
            if (key_temp == S_key)             //又一次单击（间隔肯定<500ms）
            {  
                 key_return = D_key;           //返回双击事件，回初始状态
                 key_m = key_state_0;  
            }  
            else                                 
            {                                  //这里500MS内肯定读到的都是无键事件，因为长键>100ms,在1s前底层返回的都是无键ê??T?ü  
                 if(++key_time_1 >= 5)  
                 {  
                      key_return = S_key;      // 500ms内没有再次出现单击时间，返回上一次的单击时间
                      key_m = key_state_0;     //返回出事状态
                 }  
             }  
             break;  
    } 
    return key_return;  
}




