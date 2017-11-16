/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************
 * �ļ���  ��key_scan.c
 * ����    ���������ú�����   
 * ʵ��ƽ̨��iCreate STM8������
 * ��汾  ��V2.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20
  
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
  //GPC->PIN6 ���ö˿�PE->5�������������Ĵ���Ϊ���뷽�� , ������������ , ʹ���ⲿ�ж�
  GPIO_Init(GPIOE , GPIO_PIN_5 , GPIO_MODE_IN_PU_IT);  
  
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE , EXTI_SENSITIVITY_FALL_ONLY); //PC�˿�Ϊ�½��ش����ж�
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
                                if(Aold)//��ť����
				{
                                        st=0;
                                        add_flag=1;
                                        dec_flag=0; 
                                        
                                      } 
                                
				if(Bold)   				//��ť��С
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

    key_press = SW02 ;                    // ��ȡIO��ƽ

    switch (key_state)  
    {  
      	case key_state_0:                              // ������ʼ̬
        if (!key_press) key_state = key_state_1;      //���������£�״̬ת����������ȷ��״̬ 
        break;  
        
      	case key_state_1:                      //����������ȷ��̬
        if (!key_press)  
        {  
             key_time = 0;                   //   
             key_state = key_state_2;   // ������Ȼ�����£�������ɣ�״̬ת�������¼�ʱ��ļ�ʱ״̬�������صĻ����޼��¼�  
        }  
        else  
             key_state = key_state_0;   //������̧��ת����������ʼ̬���˴���ɺ�ʵ�������������ʵ�����İ��º��ͷŶ��ڴ�����
        break;  
        
      	case key_state_2:  
        if(key_press)  
        {  
             key_return = S_key;        // ��ʱ�����ͷţ�˵���ǲ���һ�ζ̲���������S_key
             key_state = key_state_0;   // ת������ʼ̬
        }  
        else if (++key_time >= 20)     //�������£���ʱ��10ms��10msΪ������ѭ��ִ�м����
        {  
             key_return = L_key;        // ����ʱ��>1000ms,�ΰ���Ϊ���������������س����¼� 
             key_state = key_state_3;   //ת�����ȴ������ͷ�״̬
        }  
        break;  

      	case key_state_3:                 // �ȴ������ͷ�״̬����״ֻ̬�����ް����¼�
        if (key_press) key_state = key_state_0; //�������ͷţ�ת����������ʼ̬
        break;  
    }  
    return key_return;  
}

/*********************************************************************************************************
** �������ƣ�key_read
** �����������ȸ���key_driver��״ָ̬ʾ���ٸ��ݰ�����״̬��ȷ�������ǲ������̰���������˫����
**
** ����: key_driver
**
** �������
**         
**ȫ�ֱ�������

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
                 key_time_1 = 0;               //��1�ε����������أ�����һ��״̬�жϺ����Ƿ����˫��
                 key_m = key_state_1;  
            }  
            else  
                 key_return = key_temp;        //�����޼�������������ԭ�¼�
            break;  

        	case key_state_1:  
            if (key_temp == S_key)             //��һ�ε���������϶�<500ms��
            {  
                 key_return = D_key;           //����˫���¼����س�ʼ״̬
                 key_m = key_state_0;  
            }  
            else                                 
            {                                  //����500MS�ڿ϶������Ķ����޼��¼�����Ϊ����>100ms,��1sǰ�ײ㷵�صĶ����޼���??T?��  
                 if(++key_time_1 >= 5)  
                 {  
                      key_return = S_key;      // 500ms��û���ٴγ��ֵ���ʱ�䣬������һ�εĵ���ʱ��
                      key_m = key_state_0;     //���س���״̬
                 }  
             }  
             break;  
    } 
    return key_return;  
}




