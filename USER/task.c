#include "stm8s.h"
#include "task.h"
#include "key_scan.h"
#include "seg.h"
#include "tim2.h"
#include "RS232command.h"
#include "CRC_8.h"
char key_count;
extern u8 short_key_flag;// 短按标志
extern u8 key_long_down; //长按标志
extern u8 doubleClick;   //双击标志
extern u8 thirClick;//三击标志
extern u8 add_flag; //慢加标志
extern u8 quick_add_flag;//快加标志
extern u8 dec_flag;//慢减标志
extern u8 quick_dec_flag;//快减标志
extern u8 USART_RX_BUF[]; 
extern u8 flag_232_rx;
extern int Pmode7_flag;
extern int Pmode8_flag;
int js=0; 
int wei;
int last0=1;
int command_flag=0,command_time=0;
int CHX_3=1,MAXoutput_Voltage[8]={4,5,12,20,22,24,26,28},Maxoutput_re=0;

int input_state[5]={0};
int IO_output_state[5]={0};
int CPU_temperature[5]={0};
int baud_sign=1;

int IP[8]={1,0,2,0,3,0,4,0};
int Mask[8]={1,0,2,0,3,0,4,0};             
int Gateway[8]={1,0,2,0,3,0,4,0};
int Remote_IP[8]={1,0,2,0,3,0,4,0};
int Tcp_IP[5]={0,0,0,0,0};
int Remote_TcpIP[5]={0,0,0,0,0};
int Version[5]={0,0,0,0,0,};
int Factory_reset=0;
int System_restart=0;

int MODE1[5]={1,0,0,0,0};
int MODE2[5]={1,0,0,0,0};
int MODE3[5]={1,0,0,0,0};
int MODE4[5]={1,0,0,0,3};
int MODE5[5]={1,0,0,0,0};
int MODE6[5]={1,0,0,0,0};

#define MY_LONGKEY 		3 
#define MY_SHORTKEY 	1
#define MY_DOUBLEKEY 	2
#define MY_PLUSKEY  	5
#define MY_POUKEY		7

enum myenum {LHRUN,MYSAVE,MYYES,MYERR0,PXX,P001,P002,P003,P004,P005,P006,P007,P008,P009,P010,
				P011,P012,P013,P014,P015,P016,P017,P018,P019,P020}Pmode;
enum myenum list=P001;
enum myenum P_ALL=P020;

bool mode_flag=TRUE; 
bool sav_flag=FALSE;

int datawait=0;	//数据等待
extern u16 USART_RX_STA; 
extern u8 USART_RX_BUF[100];

//数据接收开始预处理
bool DatareceiveStart()
{
	datawait=20;
	while((USART_RX_STA&0x8000)==0)
	{
		if(datawait==0)
			break;
	}
	if(USART_RX_STA&0x8000)
	{
		return TRUE;
	}
	return FALSE;
}
//数据接收完成清除标志位
void DatareceiveEnd()
{
	USART_RX_STA=0;
}


//键值处理
int key_NUM()
{ 
   static u8 keyvalue=0;  
  
   if(double_key==1)
   	{
   	 keyvalue=2;
     double_key=0;
	 return keyvalue;
    }  //双击
   	if(short_key==1)
	{
	  keyvalue=1;
	  short_key=0; 
	  return keyvalue;
    } //单击
	if(long_key==1)
	{
	  keyvalue=3;
	  long_key=0; 
	  return keyvalue;
	} //长按
	 if(add_flag==1)
	{
	  keyvalue=5;
	  add_flag=0;
	  return keyvalue;
	}//慢加 
	if(dec_flag==1)
	{ 
	  keyvalue=7;
	  dec_flag=0;
	  return keyvalue;
	} //慢减
     keyvalue=0; 
     return keyvalue;
 
}
//数据解析器
int Data_AnalysePlusOrLess(int *ch,int *start,int datastart,int dataend,int chx,int setwei,u8 PluseOrLess)
{
	if(setwei<=4)
	{
	if(PluseOrLess==1)
	{
		if(setwei==0)
		{
			if(((*ch)+1)<=chx)
			{
				(*ch)++;
			}else
			{
				(*ch)=1;
			}
		}

		if(setwei==1)
		{
			if(((*start)+1000)<=dataend)
			{
				(*start)+=1000;
			}
			else
			{
				(*start)=datastart;
			}

		}
		if(setwei==2)
		{
			if(((*start)+100)<=dataend)
			{
				(*start)+=100;
			}
			else
			{
				(*start)=datastart;
			}
		}		
		if(setwei==3)
		{
			if(((*start)+10)<=dataend)
			{
				(*start)+=10;
			}
			else
			{
				(*start)=datastart;
			}
		}
		if(setwei==4)
		{
			if(((*start)+1)<=dataend)
			{
				(*start)++;
			}
			else
			{
				(*start)=datastart;
			}
		}

	}
	else
	{
		if(setwei==0)
				{
					if(((*ch)-1)>=1)
					{
						(*ch)--;
					}
					else
					{
						(*ch)=chx;
					}
				}
		
				if(setwei==1)
				{
					if(((*start)-1000)>=datastart)
					{
						(*start)-=1000;
					}
					else
					{
						(*start)=dataend;
					}
		
				}
				if(setwei==2)
				{
					if(((*start)-100)>=datastart)
					{
						(*start)-=100;
					}
					else
					{
						(*start)=dataend;
					}
				}		
				if(setwei==3)
				{
					if(((*start)-10)>=datastart)
					{
						(*start)-=10;
					}
					else
					{
						(*start)=dataend;
					}
				}
				if(setwei==4)
				{
					if(((*start)-1)>=datastart)
					{
						(*start)--;
					}
					else
					{
						(*start)=dataend;
					}
				}
	}	
	}
}
//按键分析器
void Scan_Data(bool Y_N_Double,bool Y_N_Long,bool Y_N_Sav)
{
	
	if((js==MY_DOUBLEKEY)&&(Y_N_Double==TRUE)) 
	{  
	    js=0;
	    wei=0;
		Pmode=PXX; 
		mode_flag=TRUE;
		return;
	} 

	if((js==MY_LONGKEY)&&(sav_flag==TRUE)&&(Y_N_Sav==TRUE))
     {
     	sav_flag=FALSE;
        js=0;
      	Pmode=MYSAVE;
		mode_flag=TRUE;
		return;
     }    
	
	if((js==MY_LONGKEY)&&(Y_N_Long==TRUE))//确定
	{
		 sav_flag=TRUE;
		 js=0;
		 display1(29,32,33,34,35,0X1E); //SAVE
	}	 
	mode_flag=FALSE;

}
//显示菜单
void HELL_SHOW()
{  

     js=key_NUM();
     if((js==0)&&(mode_flag==FALSE) )return ;
    switch(Pmode)
    {
      case LHRUN:     LH_RUN();  break;
	  case MYSAVE:    SAVE();    break;
	  case MYYES:     YES();    break;
	  case MYERR0:    ERR0();    break;
	  case PXX:       P_XX();    break;
      case P001:      P_001();   break;
      case P002:      P_002();   break;
      case P003:      P_003();   break;
	  case P004:      P_004();	break;
	  case P005:      P_005();   break;
 	  default :break;
    } 

}
//主页
void LH_RUN()
{
   display1(20,21,28,23,24,0X1C);
   if(js==MY_SHORTKEY)
    {
        js=0;
       Pmode=PXX;
	   mode_flag=TRUE;
	   return;
    }
      mode_flag=FALSE;
}
//保存界面
void SAVE()
{
	display1(29,39,40,30,29,0xE);
	Scan_Data(TRUE,FALSE,FALSE);
}
//确认操作
void YES()
{


}
//错误代码
void ERR0()
{


}
//主菜单
void P_XX()
{ 
   if(js==MY_PLUSKEY)
   	{
   		list+=1;
        js=0; 
        wei=0;
    }
   if(js==MY_POUKEY) 
   	{  
   		list-=1;
   		js=0;
   		wei=0; 
   	}  
   if(list>P_ALL) 
    {
    	list=P001;
    }
   else
   if(list<P001)
	{
	 	list=P_ALL;
	}
   
   if(js==MY_DOUBLEKEY) 
   	{  
   		Pmode=LHRUN; 
		mode_flag=TRUE;
		return;
    } 
       
    if(js==MY_SHORTKEY) 
    { 
       Pmode=list;
	   mode_flag=TRUE;
	   return;
    }  	
    display1(25,26,0,(list-PXX)/10,(list-PXX)%10,0x1c);
	mode_flag=FALSE;

}
//P-001恒流恒压模式切换
void P_001()
{
	static int start=0;
	static int ch=1;
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,1,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,1,4,wei,0);
		js=0;
	} 
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}
	if(wei==1)
	 {
		wei+=3;
	 }	  
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,0X1c);   
	Scan_Data(TRUE,TRUE,TRUE);
}
//P-002设置通道输出电流
void P_002()
{
	static int start=0;
	static int ch=1;
    if(js==MY_PLUSKEY) 
	{ 
		Data_AnalysePlusOrLess(&ch,&start,20,1500,4,wei,1);
		js=0; 
	}  
    if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,20,1500,4,wei,0);
		js=0;
	} 
    if(js==MY_SHORTKEY) 
    {
      wei++;  
      js=0;
	  if(wei>4)
	  	wei=0;
    }	
	display1(ch+10,(start/1000)%10,(start/100)%10,(start/10)%10,start%10,1<<wei);   
	Scan_Data(TRUE,TRUE,TRUE);
		 
}
//P-003设置输出电压
void P_003()
{
	static int start=0;
	static int ch=1;
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,40,240,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,40,240,4,wei,0);
		js=0;
	} 

	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei==1)
	 {
		wei++;
	 }	  
	display1(ch,26,(start/100)%10,((start/10)%10)+10,start%10,1<<wei); 
	Scan_Data(TRUE,TRUE,TRUE);
		 
}
//P-004设置输出电压PWM线分等级
void P_004()
{

	static int start=0;
	static int ch=1;
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,255,8,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,255,8,wei,0);
		js=0;
	} 
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}
	if(wei==1)
	 {
		wei++;
	 }	  
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   
	Scan_Data(TRUE,TRUE,TRUE);


}
//P-005设置通道频闪脉宽
void P_005()
{
    static int start=0;
	static int ch=1;
    if(js==MY_PLUSKEY) 
	{ 
		Data_AnalysePlusOrLess(&ch,&start,0,9999,8,wei,1);
		js=0; 
	}  
    if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,9999,8,wei,0);
		js=0;
	} 
    if(js==MY_SHORTKEY) 
    {
      wei++;  
      js=0;
	  if(wei>4)
	  	wei=0;
    }	
	display1(ch+10,(start/1000)%10,(start/100)%10,(start/10)%10,start%10,1<<wei);   	  
	Scan_Data(TRUE,TRUE,TRUE);
}


