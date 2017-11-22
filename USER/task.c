#include "stm8s.h"
#include "task.h"
#include "key_scan.h"
#include "seg.h"
#include "tim2.h"
#include "RS232command.h"
#include "CRC_8.h"

#define MY_LONGKEY 		3 
#define MY_SHORTKEY 	1
#define MY_DOUBLEKEY 	2
#define MY_PLUSKEY  	5
#define MY_POUKEY		7
#define MY_THREE		12

enum myenum {LHRUN,
				MYSAVE,
				MYYES,
				MYERR0,
				PXX,
				P001,
				P002,
				P003,
				P004,
				P005,
				P006,
				P007,
				P008,
				P009,
				P010,
				P011,
				P012,
				P013,
				P014,
				P015,
				P016,
				P017,
				P018,
				P019,
				P020
				}Pmode;
enum myenum list=P001;
enum myenum P_ALL=P020;

bool mode_flag=TRUE; 
bool sav_flag=FALSE;
bool teplet=FALSE;

int js=0; 
int wei=0;

int datawait=0;	//数据等待
extern u16 USART_RX_STA; 
extern u8 USART_RX_BUF[100];


//数据接收开始预处理
bool DatareceiveStart()
{
	datawait=100;
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
//数据接收完成处理
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
	if(three_key==1)
	{
		keyvalue=12;
		three_key=0;
		return keyvalue;
	}
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
bool Scan_Data(bool Y_N_Double,bool Y_N_Long,bool Y_N_Sav)
{
	
	if((js==MY_DOUBLEKEY)&&(Y_N_Double==TRUE)) 
	{  
	    js=0;
	    wei=0;
		Pmode=PXX; 
		mode_flag=TRUE;
		return TRUE;
	} 

	if((js==MY_LONGKEY)&&(sav_flag==TRUE)&&(Y_N_Sav==TRUE))
     {
     	sav_flag=FALSE;
        js=0;
      	Pmode=MYSAVE;
		mode_flag=TRUE;
		CodeSave();
		DatareceiveStart();
		DatareceiveEnd();
		return TRUE;
     }    
	
	if((js==MY_LONGKEY)&&(Y_N_Long==TRUE))//确定
	{
		 sav_flag=TRUE;
		 js=0;
		 display1(29,32,33,34,35,0X1E); //SAVE
		 mode_flag=FALSE;
		 return TRUE;
	}
	mode_flag=FALSE;
	return FALSE;
	

}
//显示菜单
void HELL_SHOW()
{  

     js=key_NUM();
     if((js==0)&&(mode_flag==FALSE))return ;
    switch(Pmode)
    {
      case LHRUN:     LH_RUN();  break;
	  case MYSAVE:    SAVE();    break;
	  case MYYES:     YES();     break;
	  case MYERR0:    ERR0();    break;
	  case PXX:       P_XX();    break;
      case P001:      P_001();   break;
      case P002:      P_002();   break;
      case P003:      P_003();   break;
	  case P004:      P_004();	 break;
	  case P005:      P_005();   break;
	  case P006:	  P_006();	 break;
	  case P007:	  P_007();	 break;
	  case P008:	  P_008();	 break;
	  case P009:	  P_009();	 break;
	  case P010:	  P_010();	 break;
	  case P011:	  P_011();	 break;
	  case P012:	  P_012();	 break;
	  case P013:	  P_013();	 break;
	  case P014:	  P_014();	 break;
 	  default :break;
    } 

}
//主页
void LH_RUN()
{
	if(js==MY_LONGKEY)
	{
		CodeClear();
		DatareceiveStart();
		DatareceiveEnd();
		js=0;
	}

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
    display(25,26,0,(list-PXX)/10,(list-PXX)%10);
	mode_flag=FALSE;

}
//P-001恒流恒压模式切换
void P_001()
{
	static int start=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
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
	if(wei!=0)
	{
		
		CodeP001Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP001Rad(ch);
		if(DatareceiveStart())
		{
			start=USART_RX_BUF[11]-'0';
		}
		else
		{
			start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei+=3;
	 }
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   
	 
	
}
//P-002设置通道输出电流
void P_002()
{
	static int start=0;
	static int ch=1;
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
    if(js==MY_PLUSKEY) 
	{ 
		Data_AnalysePlusOrLess(&ch,&start,100,1500,4,wei,1);
		js=0; 
	}  
    if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,100,1500,4,wei,0);
		js=0;
	} 
    if(js==MY_SHORTKEY) 
    {
      wei++;  
      js=0;
	  if(wei>4)
	  	wei=0;
    }	
	if(wei!=0)
	{	
		CodeP002Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP002Rad(ch);
		if(DatareceiveStart())
		{
			start=(USART_RX_BUF[10]-'0')*1000;
			start+=(USART_RX_BUF[11]-'0')*100;
			start+=(USART_RX_BUF[12]-'0')*10;
			start+=(USART_RX_BUF[13]-'0');
		}
		else
		{
			start=100;
		}
		DatareceiveEnd();
	}	
	
	display1(ch+10,(start/1000)%10,(start/100)%10,(start/10)%10,start%10,1<<wei);   
	if(js==MY_THREE)
	{
		CodeP003004(ch);
	}
	
}
//P-003设置输出电压
void P_003()
{
	static int start=0;
	static int ch=1;
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
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
	if(wei!=0)
	{	
		CodeP003Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
		{
			CodeP003Rad(ch);
			if(DatareceiveStart())
			{
				start=(USART_RX_BUF[11]-'0')*100;
				start+=(USART_RX_BUF[12]-'0')*10;
				start+=(USART_RX_BUF[13]-'0');
			}
			else
			{
				start=100;
			}
			DatareceiveEnd();
		}	

	
	display1(ch,26,(start/100)%10,((start/10)%10)+10,start%10,1<<wei); 
	
	if(js==MY_THREE)
	{
		CodeP003004(ch);
	}
		 
}
//P-004设置输出电压PWM线分等级
void P_004()
{
	static int start=0;
	static int ch=1;
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
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
	if(wei!=0)
	{	
		CodeP004Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
		{
			CodeP004Rad(ch);
			if(DatareceiveStart())
			{
				start=(USART_RX_BUF[11]-'0')*100;
				start+=(USART_RX_BUF[12]-'0')*10;
				start+=(USART_RX_BUF[13]-'0');
			}
			else
			{
				start=100;
			}
			DatareceiveEnd();
		}	
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   
	


}
//P-005设置通道频闪脉宽
void P_005()
{
	static int start=0;
	static int ch=1;
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
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
	if(wei!=0)
	{	
		CodeP005Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP005Red(ch);
		if(DatareceiveStart())
		{
			start=(USART_RX_BUF[10]-'0')*1000;
			start+=(USART_RX_BUF[11]-'0')*100;
			start+=(USART_RX_BUF[12]-'0')*10;
			start+=(USART_RX_BUF[13]-'0');
		}
		else
		{
			start=100;
		}
		DatareceiveEnd();
	}	
	
	display1(ch+10,(start/1000)%10,(start/100)%10,(start/10)%10,start%10,1<<wei);   
	
}

void P_006()
{
	static int start=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,1,8,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,1,8,wei,0);
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei!=0)
	{
		
		CodeP006Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP006Red(ch);
		if(DatareceiveStart())
		{
			start=USART_RX_BUF[12]-'0';
		}
		else
		{
			start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei+=3;
	 }
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   
	 
	
}

void P_007()
{
	static int start=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,3,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,3,4,wei,0);
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei!=0)
	{
		
		CodeP007Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP007Rad(ch);
		if(DatareceiveStart())
		{
			start=USART_RX_BUF[12]-'0';
		}
		else
		{
			start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei+=3;
	 }
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   

	 
	
}

void P_008()
{
	static int start=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,3,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,3,4,wei,0);
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei!=0)
	{
		
		CodeP008Set(ch,start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodeP008Red(ch);
		if(DatareceiveStart())
		{
			start=USART_RX_BUF[12]-'0';
		}
		else
		{
			start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei+=3;
	 }
	display1(ch,26,(start/100)%10,((start/10)%10),start%10,1<<wei);   

	 
	
}

void P_009()
{
	static int start=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
	    teplet=FALSE;
		return;
	}
	teplet=TRUE;
	CodeP009Red();
	if(DatareceiveStart())
	{
		start=(USART_RX_BUF[11]-'0')*1000;
		start+=(USART_RX_BUF[12]-'0')*100;
		start+=(USART_RX_BUF[13]-'0')*10;
		start+=(USART_RX_BUF[14]-'0');
	}
	else
	{
		start=0;
	}
	DatareceiveEnd();	
	
	display(26,(start/1000)%10,(start/100)%10,((start/10)%10),start%10);   

	 
	
}

void P_010()
{
	static int start[5]=0;
	static int ch=1;  
	CodeP010Rad();
	if(DatareceiveStart())
	{	
		start[0]=(USART_RX_BUF[11]-'0')*10000;
		start[1]+=(USART_RX_BUF[12]-'0')*1000;
		start[2]+=(USART_RX_BUF[13]-'0')*100;
		start[3]+=(USART_RX_BUF[14]-'0')*10;
		start[4]+=(USART_RX_BUF[15]-'0');
	}
	else
	{
		//start=0;
	}
	DatareceiveEnd();	
	
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	
	if(js==MY_PLUSKEY) 
	{

		if(start[wei]+1==1)
		{
			start[wei]=1;
		}else
		{
			start[wei]=0;
		}
		
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		if(start[wei]-1==0)
		{
			start[wei]=0;
		}else
		{
			start[wei]=1;
		}
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	
	CodeP010Set(start);	
	DatareceiveStart();
	DatareceiveEnd();
	
	display1(start[0],start[1],start[2],start[3],start[4],1<<wei);   	 
	
}

void P_011()
{
	static int start=0;
	static int ch=1;  

	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
	    teplet=FALSE;
		return;
	}
	teplet=TRUE;
	CodeP011Red();
	if(DatareceiveStart())
	{
		start=(USART_RX_BUF[9]-'0')*1000;
		start+=(USART_RX_BUF[10]-'0')*100;
		start+=(USART_RX_BUF[12]-'0')*10;
		start+=(USART_RX_BUF[13]-'0');
	}
	else
	{
		start=0;
	}
	DatareceiveEnd();			
	display((start/1000)%10,(start/100)%10+10,((start/10)%10),start%10,30);
}

void P_012()
{
	static int start=0;
	static int ch=1;  
	
	CodeP012Red();
	if(DatareceiveStart())
	{
		start=USART_RX_BUF[9]-'0';
	}
	else
	{
		start=0;
	}
	DatareceiveEnd();	
	
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start,0,7,1,4,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start,0,7,1,4,0);
		js=0;
	}	
	
	CodeP012Set(start);
	DatareceiveStart();
	DatareceiveEnd();	
	
	display1(0,0,0,0,start,1<<4);
}
//控制器IP地址
void P_013()
{
	int i=0;
	int temp=25;

	static int start[4]=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start[ch-1],0,255,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start[ch-1],0,255,4,wei,0);
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei!=0)
	{	
		CodeP013Set(start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodePIPRea();
		if(DatareceiveStart())
		{
			for(;i<4;i++)
			{
				start[i]=(USART_RX_BUF[temp++]-'0')*100;
				start[i]+=(USART_RX_BUF[temp++]-'0')*10;
				start[i]+=(USART_RX_BUF[temp++]-'0');
				temp++;
			}
		}
		else
		{
			//start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei++;
	 }
	
	display1(ch,26,(start[ch-1]/100)%10,((start[ch-1]/10)%10),start[ch-1]%10,1<<wei);   
	 
}

//子网掩码
void P_014()
{
	int i=0;
	int temp=41;

	static int start[4]=0;
	static int ch=1;  
	if(Scan_Data(TRUE,TRUE,TRUE)==TRUE)
	{
		return;
	}
	if(js==MY_PLUSKEY) 
	{
		Data_AnalysePlusOrLess(&ch,&start[ch-1],0,255,4,wei,1);
		js=0; 
	}  
	if(js==MY_POUKEY)
	{
		Data_AnalysePlusOrLess(&ch,&start[ch-1],0,255,4,wei,0);
		js=0;
	} 	
	if(js==MY_SHORTKEY) 
	{
	  wei++;  
	  js=0;
	  if(wei>4)
	  wei=0;
	}	
	if(wei!=0)
	{	
		CodeP014Set(start);	
		DatareceiveStart();
		DatareceiveEnd();
	}	
	if(wei==0)
	{
		CodePIPRea();
		if(DatareceiveStart())
		{
			for(;i<4;i++)
			{
				start[i]=(USART_RX_BUF[temp++]-'0')*100;
				start[i]+=(USART_RX_BUF[temp++]-'0')*10;
				start[i]+=(USART_RX_BUF[temp++]-'0');
				temp++;
			}
		}
		else
		{
			//start=0;
		}
		DatareceiveEnd();
	}	
	
	if(wei==1)
	 {
		wei++;
	 }
	
	display1(ch,26,(start[ch-1]/100)%10,((start[ch-1]/10)%10),start[ch-1]%10,1<<wei);   
	 
}








