#include "seg.h"

#include "stm8s.h"


 u16 Counttime_ms=0;
 u8 ds[SMG_weinum]={1,2,3,4,5};//ʵ����ʾ��
 u8 dss[SMG_weinum]={1,2,3,4,5};//��Ҫ��ʾ��
 u8 blink=0;;
 u8  tab_num[]={	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,  //0~9 
                        0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,   //С����  //10~19
                        0x38,0xf6,0x77,0x1c,0x54,                              //LH.Run//20~24
                        0x73,0x40,                              //P-           //25~26
                        0x79,0x50,                           //Er           //27~28
                        0x00,                                //��             //29
                        0x39,                                  //C            //30
                        0x31,                                    //r  //31
                        0x6d,0x77,0x3E,0x79,                      //SAVE   32~35        
                        0x58,                                     //c  36
                        0x6e,0x79,0x6d ,                        //YES  37~39 
                        0x3e,0xff};                                 //U 40
 
void smg_write(u8 a)	
{
  
    GPIO_Write(GPIOB, a);    

     if(0x10&a) seg_e_GPIO->ODR |= seg_e;  else seg_e_GPIO->ODR  &=~ seg_e;
     if(0x20&a) seg_f_GPIO->ODR |= seg_f;  else seg_f_GPIO->ODR  &=~ seg_f; 
     
  
}
void display(u8 a1,u8 a2,u8 a3,u8 a4,u8 a5)
{
   u8 i=0;
    dss[4]=a5;
    dss[3]=a4;
    dss[2]=a3;
    dss[1]=a2;
    dss[0]=a1;    
    blink=0;;
 for(;i<5;i++)
    {ds[i]=dss[i];}
}
void display1(u8 a1,u8 a2,u8 a3,u8 a4,u8 a5 ,u8 a6)
{
  u8 i=0;
    dss[4]=a5;
    dss[3]=a4;
    dss[2]=a3;
    dss[1]=a2;
    dss[0]=a1;
    blink=a6;
    for(;i<5;i++)
    {ds[i]=dss[i];}
 
}

void smgqp(void)
{
	smg_write(0xff);
	smg_l(0xf);
}

void smg_l(u8 a)
{
	switch(a)
	{
          case 0:
		{		
            seg_wei1_GPIO->ODR &=~seg_wei1;//�õ�
            seg_wei2_GPIO->ODR &=~seg_wei2;//�õ�
            seg_wei3_GPIO->ODR &=~seg_wei3;//�õ�
            seg_wei4_GPIO->ODR &=~seg_wei4;//�õ�
            seg_wei5_GPIO->ODR &=~seg_wei5;//�õ�
		}break;
		case 1:
		{		
            seg_wei1_GPIO->ODR &=~seg_wei1;//�õ�
            seg_wei2_GPIO->ODR |= seg_wei2;//�ø�
            seg_wei3_GPIO->ODR |= seg_wei3;//�ø�
            seg_wei4_GPIO->ODR |= seg_wei4;//�ø�
            seg_wei5_GPIO->ODR |= seg_wei5;//�ø�
		}break;
		case 2:
		{
	    seg_wei2_GPIO->ODR &=~seg_wei2;//�õ�
            seg_wei1_GPIO->ODR |= seg_wei1;//�ø�
            seg_wei3_GPIO->ODR |= seg_wei3;//�ø�
            seg_wei4_GPIO->ODR |= seg_wei4;//�ø�
            seg_wei5_GPIO->ODR |= seg_wei5;//�ø�
		}break;
		case 3:
		{
            seg_wei3_GPIO->ODR &=~seg_wei3;//�õ�
            seg_wei1_GPIO->ODR |= seg_wei1;//�ø�
            seg_wei2_GPIO->ODR |= seg_wei2;//�ø�
            seg_wei4_GPIO->ODR |= seg_wei4;//�ø�
            seg_wei5_GPIO->ODR |= seg_wei5;//�ø�
		}break;
		case 4:
		{
	    seg_wei4_GPIO->ODR &=~seg_wei4;//�õ�
            seg_wei1_GPIO->ODR |= seg_wei1;//�ø�
            seg_wei2_GPIO->ODR |= seg_wei2;//�ø�
            seg_wei3_GPIO->ODR |= seg_wei3;//�ø�
            seg_wei5_GPIO->ODR |= seg_wei5;//�ø�
		}break;
		case 5:
		{
	    seg_wei5_GPIO->ODR &=~seg_wei5;//�õ�
            seg_wei1_GPIO->ODR |= seg_wei1;//�ø�
            seg_wei2_GPIO->ODR |= seg_wei2;//�ø�
            seg_wei3_GPIO->ODR |= seg_wei3;//�ø�
            seg_wei4_GPIO->ODR |= seg_wei4;//�ø�
		}break;		
		case 0xf:
		{
            seg_wei1_GPIO->ODR |= seg_wei1;//�ø�
            seg_wei2_GPIO->ODR |= seg_wei2;//�ø�
            seg_wei3_GPIO->ODR |= seg_wei3;//�ø�
            seg_wei4_GPIO->ODR |= seg_wei4;//�ø�
            seg_wei5_GPIO->ODR |= seg_wei5;//�ø�
		}break;
	}
}
void seg_Init(void)
{
      //����IO��Ϊ���
    seg_a_GPIO->DDR |=seg_a;//���ģʽ
    seg_a_GPIO->CR1 |=seg_a;//�������

    seg_b_GPIO->DDR |=seg_b;//���ģʽ
    seg_b_GPIO->CR1 |=seg_b;//�������

    seg_c_GPIO->DDR |=seg_c;//���ģʽ
    seg_c_GPIO->CR1 |=seg_c;//�������

    seg_d_GPIO->DDR |=seg_d;//���ģʽ
    seg_d_GPIO->CR1 |=seg_d;//�������

    seg_e_GPIO->DDR |=seg_e;//���ģʽ
    seg_e_GPIO->CR1 |=seg_e;//�������

    seg_f_GPIO->DDR |=seg_f;//���ģʽ
    seg_f_GPIO->CR1 |=seg_f;//�������

    seg_g_GPIO->DDR |=seg_g;//���ģʽ
    seg_g_GPIO->CR1 |=seg_g;//�������

    seg_dp_GPIO->DDR |=seg_dp;//���ģʽ
    seg_dp_GPIO->CR1 |=seg_dp;//�������


    seg_wei1_GPIO->DDR |=seg_wei1;//���ģʽ
    seg_wei1_GPIO->CR1 |=seg_wei1;//�������

    seg_wei2_GPIO->DDR |=seg_wei2;//���ģʽ
    seg_wei2_GPIO->CR1 |=seg_wei2;//�������

    seg_wei3_GPIO->DDR |=seg_wei3;//���ģʽ
    seg_wei3_GPIO->CR1 |=seg_wei3;//�������
    
    seg_wei4_GPIO->DDR |=seg_wei4;//���ģʽ
    seg_wei4_GPIO->CR1 |=seg_wei4;//�������
    
    seg_wei5_GPIO->DDR |=seg_wei5;//���ģʽ
    seg_wei5_GPIO->CR1 |=seg_wei5;//�������
    
    display1(29,29,29,29,29,0);//��ʼ����Ϩ��ȴ�����
   //display1(41,41,41,41,41,0);  
}



void smxs(void)
{

 u8 i=0; 
 static  u8 num=0;

 if( blink!=0) 
 {
  
     Counttime_ms++;
     if(Counttime_ms==350)   //��������
     {
        for(;i<5;i++)
        {
          if((blink&(1<<i))!=0)
            ds[i]=29;
        }
     }
     else if(Counttime_ms==750)// ������ʾ����
     {
        Counttime_ms=0;
         for(;i<5;i++)
          {ds[i]=dss[i];}
     
     }
     
 
 } 

 else
  Counttime_ms=0;
    switch(num)
     {
        case 0:   smg_l(num+1); smg_write(tab_num[ds[num]]);break;
        case 1:   smg_l(num+1); smg_write(tab_num[ds[num]]);break;
        case 2:   smg_l(num+1); smg_write(tab_num[ds[num]]);break;
        case 3:   smg_l(num+1); smg_write(tab_num[ds[num]]);break;
        case 4:   smg_l(num+1); smg_write(tab_num[ds[num]]);break;
        
        }       
       num++;
       if(num==5) num=0; 
       
}


