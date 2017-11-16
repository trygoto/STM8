#include "RS232command.h"
#include "UART2.h"
#include "CRC_8.h"

u8 send_buffer[200];

void gmemcpy(void *pDst, const void *pSrc, unsigned long iNum)
{
	unsigned long  i;
	char *ucdst;
	char *ucsrc;
	
	ucdst = (char *)pDst;
	ucsrc = (char *)pSrc;
	
	for(i=0; i<iNum; ++i)
	{
		*ucdst++ = *ucsrc++;
	}
}

//������ѹģʽ����
void CodeP001Set(int chx,int VoltageCurrent)
{
 	gmemcpy(send_buffer,"IDC,SMIV,1,1,?,\r\n",17);
 	send_buffer[9]=chx+'0';
 	send_buffer[11]=VoltageCurrent+'0';
	send_buffer[13]=CRC8_Table(send_buffer, 13);
 	UART2_SendString(send_buffer,17);
}
//������ѹģʽ��ȡ
void CodeP001Rad(int chx)
{
 	gmemcpy(send_buffer,"IDC,GMIV,1,?,\r\n",15);
 	send_buffer[9]=chx+'0';
	send_buffer[11]=CRC8_Table(send_buffer, 11);
 	UART2_SendString(send_buffer,15);
}
//�����������
void CodeP002Set(int chx,int Current)
{
	gmemcpy(send_buffer,"IDC,SLI,1,0012,��,\r\n",19);
 	send_buffer[8]=chx+'0';
	send_buffer[10]=((Current/1000)%10)+'0';
	send_buffer[11]=((Current/100)%10)+'0';
	send_buffer[12]=((Current/10)%10)+'0';
	send_buffer[13]=(Current%10)+'0';
	
	send_buffer[15]=CRC8_Table(send_buffer, 15);
 	UART2_SendString(send_buffer,19);

}
//��ȡ�������
void CodeP002Rad(int chx)
{
	gmemcpy(send_buffer,"IDC,GLI,1,��,\r\n",14);
 	send_buffer[8]=chx+'0';
	
	send_buffer[10]=CRC8_Table(send_buffer, 10);
 	UART2_SendString(send_buffer,14);	

}
//���������ѹ
void CodeP003Set(int chx,int Voltage)
{

	gmemcpy(send_buffer,"IDC,SVOT,1,123,?,\r\n",19);
 	send_buffer[9]=chx+'0';
	
 	send_buffer[11]=((Voltage/100)%10)+'0';
	send_buffer[12]=((Voltage/10)%10)+'0';
	send_buffer[13]=(Voltage%10)+'0';
	
	send_buffer[15]=CRC8_Table(send_buffer, 15);
 	UART2_SendString(send_buffer,19);	
}

//��ȡ�����ѹ
void CodeP003Rad(int chx)
{
 	gmemcpy(send_buffer,"IDC,GVOT,1,��,\r\n",14);
	send_buffer[9]=chx+'0';

	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);	
}

//���������ѹPWM
void CodeP004Set(int chx,int VoltagePWM)
{

	gmemcpy(send_buffer,"IDC,SPWM,1,123,?,\r\n",19);
 	send_buffer[9]=chx+'0';
	
 	send_buffer[11]=((VoltagePWM/100)%10)+'0';
	send_buffer[12]=((VoltagePWM/10)%10)+'0';
	send_buffer[13]=(VoltagePWM%10)+'0';
	
	send_buffer[15]=CRC8_Table(send_buffer, 15);
 	UART2_SendString(send_buffer,19);	
}

//��ȡ�����ѹPWM
void CodeP004Rad(int chx)
{
 	gmemcpy(send_buffer,"IDC,GPWM,1,��,\r\n",14);
	send_buffer[9]=chx+'0';

	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);	
}








void RS232_command22(int num1,int num2,int num3,int num4)//带参数打开通道
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='O';
 send_buffer[5]='P';
 send_buffer[6]='S';
 send_buffer[7]='P';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=',';
 send_buffer[11]=num2+48;
 send_buffer[12]=num3+48;
 send_buffer[13]=num4+48;
 send_buffer[14]=',';
 send_buffer[15]=CRC8_Table(send_buffer, 15);//CRC;
 send_buffer[16]=',';
 send_buffer[17]=0x0D;
 send_buffer[18]=0x0A;
 UART2_SendString(send_buffer,19);
  
}
void RS232_command2(int num)//查询频闪
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='T';
 send_buffer[6]='R';
 send_buffer[7]=',';
 send_buffer[8]=num+48;
 send_buffer[9]=',';
 send_buffer[10]=CRC8_Table(send_buffer, 10);//CRC;
 send_buffer[11]=',';
 send_buffer[12]=0x0D;
 send_buffer[13]=0x0A;
 UART2_SendString(send_buffer,14);
}

void RS232_command23(int num1,int num2,int num3,int num4,int num5)//设置频闪脉宽
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='T';
 send_buffer[6]='R';
 send_buffer[7]=',';
 send_buffer[8]=num1+48;
 send_buffer[9]=',';
 send_buffer[10]=num2+48;
 send_buffer[11]=num3+48;
 send_buffer[12]=num4+48;
 send_buffer[13]=num5+48;
 send_buffer[14]=',';
 send_buffer[15]=CRC8_Table(send_buffer, 15);//CRC;
 send_buffer[16]=',';
 send_buffer[17]=0x0D;
 send_buffer[18]=0x0A;
 UART2_SendString(send_buffer,19);
  
}

void RS232_command3(int num)//查询电压
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='V';
 send_buffer[6]='O';
 send_buffer[7]='T';
 send_buffer[8]=',';
 send_buffer[9]=num+48;
 send_buffer[10]=',';
 send_buffer[11]=CRC8_Table(send_buffer, 11);//CRC;
 send_buffer[12]=',';
 send_buffer[13]=0x0D;
 send_buffer[14]=0x0A;
 UART2_SendString(send_buffer,15);
  
}
void RS232_command24(int num1,int num2)//设置电压
{
  int out;
 if(num2==4) out=0;
 else if(num2==5) out=1;
 else if(num2==12) out=2;
 else if(num2==20) out=3;
 else if(num2==22) out=4;
 else if(num2==24) out=5;
 else if(num2==26) out=6;
 else if(num2==28) out=7;
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='V';
 send_buffer[6]='O';
 send_buffer[7]='T';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=',';
 send_buffer[11]=out+48;

 send_buffer[12]=',';
 send_buffer[13]=CRC8_Table(send_buffer, 13);//CRC;
 send_buffer[14]=',';
 send_buffer[15]=0x0D;
 send_buffer[16]=0x0A;
 UART2_SendString(send_buffer,17);
  
}
void RS232_command4(int num)//查询外部触发方式
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='E';
 send_buffer[6]='X';
 send_buffer[7]='M';
 send_buffer[8]=',';
 send_buffer[9]=num+48;
 send_buffer[10]=',';
 send_buffer[11]=CRC8_Table(send_buffer, 11);//CRC;
 send_buffer[12]=',';
 send_buffer[13]=0x0D;
 send_buffer[14]=0x0A;
 UART2_SendString(send_buffer,15);
  
}
                    
 void RS232_command25(int num1,int num2)//设置外部触发方式
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='E';
 send_buffer[6]='X';
 send_buffer[7]='M';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=',';
 send_buffer[11]=num2+48;
 send_buffer[12]=',';
 send_buffer[13]=CRC8_Table(send_buffer, 13);//CRC;
 send_buffer[14]=',';
 send_buffer[15]=0x0D;
 send_buffer[16]=0x0A;
 UART2_SendString(send_buffer,17);
  
}
void RS232_command5(int num )//查询通道默认输出模式
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='M';
 send_buffer[6]='O';
 send_buffer[7]='U';
 send_buffer[8]='T';
 send_buffer[9]=',';
 send_buffer[10]=num+48;
 send_buffer[11]=',';
 send_buffer[12]=CRC8_Table(send_buffer, 12);//CRC;
 send_buffer[13]=',';
 send_buffer[14]=0x0D;
 send_buffer[15]=0x0A;
 UART2_SendString(send_buffer,16);
  
}
void RS232_command26(int num1,int num2)//设置通道默认输出模式
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='M';
 send_buffer[6]='O';
 send_buffer[7]='U';
 send_buffer[8]='T';
 send_buffer[9]=',';
 send_buffer[10]=num1+48;
 send_buffer[11]=',';
 send_buffer[12]=num2+48;
 send_buffer[13]=',';
 send_buffer[14]=CRC8_Table(send_buffer, 14);//CRC;
 send_buffer[15]=',';
 send_buffer[16]=0x0D;
 send_buffer[17]=0x0A;
 UART2_SendString(send_buffer,18);
  
}
                    
void RS232_command6(int num)//查询外部IO接口工作模式
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='I';
 send_buffer[6]='O';
 send_buffer[7]='M';
 send_buffer[8]=',';
 send_buffer[9]=num+48;
 send_buffer[10]=',';
 send_buffer[11]=CRC8_Table(send_buffer, 11);//CRC;
 send_buffer[12]=',';
 send_buffer[13]=0x0D;
 send_buffer[14]=0x0A;
 UART2_SendString(send_buffer,15);
  
}
                    
void RS232_command27(int num1,int num2)//设置外部IO接口工作模式
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='I';
 send_buffer[6]='O';
 send_buffer[7]='M';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=',';
 send_buffer[11]=num2+48;
 send_buffer[12]=',';
 send_buffer[13]=CRC8_Table(send_buffer, 13);//CRC;
 send_buffer[14]=',';
 send_buffer[15]=0x0D;
 send_buffer[16]=0x0A;
 UART2_SendString(send_buffer,17);
  
}

void RS232_command7()//获取输入IO状�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='I';
 send_buffer[5]='O';
 send_buffer[6]='R';
 send_buffer[7]='B';
 send_buffer[8]='I';
 send_buffer[9]='T';
 send_buffer[10]=',';
 send_buffer[11]=CRC8_Table(send_buffer, 11);//CRC;
 send_buffer[12]=',';
 send_buffer[13]=0x0D;
 send_buffer[14]=0x0A;
 UART2_SendString(send_buffer,15);
  
}
void RS232_command8()//查询输出IO电平状�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='I';
 send_buffer[5]='O';
 send_buffer[6]='G';
 send_buffer[7]='R';
 send_buffer[8]='B';
 send_buffer[9]='I';
 send_buffer[10]='T';
 send_buffer[11]=',';
 send_buffer[12]=CRC8_Table(send_buffer, 12);//CRC;
 send_buffer[13]=',';
 send_buffer[14]=0x0D;
 send_buffer[15]=0x0A;
 UART2_SendString(send_buffer,16);
 
  
  
}
                    
void RS232_command34(int num1,int num2,int num3,int num4,int num5)//设置输出IO电平状�?
{

 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='I';
 send_buffer[5]='O';
 send_buffer[6]='W';
 send_buffer[7]='B';
 send_buffer[8]='I';
 send_buffer[9]='T';
 send_buffer[10]=',';
 send_buffer[11]=num1+48;
 send_buffer[12]=num2+48;
 send_buffer[13]=num3+48;
 send_buffer[14]=num4+48;
 send_buffer[15]=num5+48;
 send_buffer[16]=',';
 send_buffer[17]=CRC8_Table(send_buffer, 17);//CRC;
 send_buffer[18]=',';
 send_buffer[19]=0x0D;
 send_buffer[20]=0x0A;
 UART2_SendString(send_buffer,21);
  
}
                    
void RS232_command9()//查询控制器内部温�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='T';
 send_buffer[6]='E';
 send_buffer[7]='M';
 send_buffer[8]=',';
 send_buffer[9]=CRC8_Table(send_buffer, 9);//CRC;
 send_buffer[10]=',';
 send_buffer[11]=0x0D;
 send_buffer[12]=0x0A;
 UART2_SendString(send_buffer,13);
  
}
void RS232_command10(int num)//设置波特�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='B';
 send_buffer[6]='T';
 send_buffer[7]='L';
 send_buffer[8]=',';
 send_buffer[9]=num+48;
 send_buffer[10]=',';
 send_buffer[11]=CRC8_Table(send_buffer, 11);//CRC;
 send_buffer[12]=',';
 send_buffer[13]=0x0D;
 send_buffer[14]=0x0A;
 UART2_SendString(send_buffer,15);
  
}
void RS232_command11(int num1,int num2,int num3,int num4)//设置IP地址
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='L';
 send_buffer[6]='I';
 send_buffer[7]='P';
 send_buffer[8]=',';
 send_buffer[9]=num1/100+48;
 send_buffer[10]=num1%100/10+48;
 send_buffer[11]=num1%10+48;
 send_buffer[12]=',';
 send_buffer[13]=num2/100+48;
 send_buffer[14]=num2%100/10+48;
 send_buffer[15]=num2%10+48;
 send_buffer[16]=',';
 send_buffer[17]=num3/100+48;
 send_buffer[18]=num3%100/10+48;
 send_buffer[19]=num3%10+48;
 send_buffer[20]=',';
 send_buffer[21]=num4/100+48;
 send_buffer[22]=num4%100/10+48;
 send_buffer[23]=num4%10+48;
 send_buffer[24]=',';
 send_buffer[25]=CRC8_Table(send_buffer, 25);//CRC;
 send_buffer[26]=',';
 send_buffer[27]=0x0D;
 send_buffer[28]=0x0A;
 UART2_SendString(send_buffer,29);
  
}
void RS232_command12(int num1,int num2,int num3,int num4)//设置子网掩码
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='N';
 send_buffer[6]='M';
 send_buffer[7]=',';
 send_buffer[8]=num1/100+48;
 send_buffer[9]=num1%100/10+48;
 send_buffer[10]=num1%10+48;
 send_buffer[11]=',';
 send_buffer[12]=num2/100+48;
 send_buffer[13]=num2%100/10+48;
 send_buffer[14]=num2%10+48;
 send_buffer[15]=',';
 send_buffer[16]=num3/100+48;
 send_buffer[17]=num3%100/10+48;
 send_buffer[18]=num3%10+48;
 send_buffer[19]=',';
 send_buffer[20]=num4/100+48;
 send_buffer[21]=num4%100/10+48;
 send_buffer[22]=num4%10+48;
 send_buffer[23]=',';
 send_buffer[24]=CRC8_Table(send_buffer, 24);//CRC;
 send_buffer[25]=',';
 send_buffer[26]=0x0D;
 send_buffer[27]=0x0A;
 UART2_SendString(send_buffer,28);
  
}
void RS232_command13(int num1,int num2,int num3,int num4)//设置网关
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='G';
 send_buffer[6]='W';
 send_buffer[7]=',';
 send_buffer[8]=num1/100+48;
 send_buffer[9]=num1%100/10+48;
 send_buffer[10]=num1%10+48;
 send_buffer[11]=',';
 send_buffer[12]=num2/100+48;
 send_buffer[13]=num2%100/10+48;
 send_buffer[14]=num2%10+48;
 send_buffer[15]=',';
 send_buffer[16]=num3/100+48;
 send_buffer[17]=num3%100/10+48;
 send_buffer[18]=num3%10+48;
 send_buffer[19]=',';
 send_buffer[20]=num4/100+48;
 send_buffer[21]=num4%100/10+48;
 send_buffer[22]=num4%10+48;
 send_buffer[23]=',';
 send_buffer[24]=CRC8_Table(send_buffer, 24);//CRC;
 send_buffer[25]=',';
 send_buffer[26]=0x0D;
 send_buffer[27]=0x0A;
 UART2_SendString(send_buffer,28);
  
}
void RS232_command14(int num1,int num2,int num3,int num4)//设置远程IP
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='R';
 send_buffer[6]='I';
 send_buffer[7]='P';
 send_buffer[8]=',';
 send_buffer[9]=num1/100+48;
 send_buffer[10]=num1%100/10+48;
 send_buffer[11]=num1%10+48;
 send_buffer[12]=',';
 send_buffer[13]=num2/100+48;
 send_buffer[14]=num2%100/10+48;
 send_buffer[15]=num2%10+48;
 send_buffer[16]=',';
 send_buffer[17]=num3/100+48;
 send_buffer[18]=num3%100/10+48;
 send_buffer[19]=num3%10+48;
 send_buffer[20]=',';
 send_buffer[21]=num4/100+48;
 send_buffer[22]=num4%100/10+48;
 send_buffer[23]=num4%10+48;
 send_buffer[24]=CRC8_Table(send_buffer, 24);//CRC;
 send_buffer[25]=',';
 send_buffer[26]=0x0D;
 send_buffer[27]=0x0A;
 UART2_SendString(send_buffer,28);
  
}
void RS232_command15(int num1,int num2,int num3,int num4)//设置TCPIP
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='L';
 send_buffer[6]='P';
 send_buffer[7]='T';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=num2+48;
 send_buffer[11]=num3+48;
 send_buffer[12]=num4+48;
 send_buffer[13]=',';  
 send_buffer[14]=CRC8_Table(send_buffer, 14);//CRC;
 send_buffer[15]=',';
 send_buffer[16]=0x0D;
 send_buffer[17]=0x0A;
 UART2_SendString(send_buffer,18);
  
}
void RS232_command16(int num1,int num2,int num3,int num4)//设置远程TCPIP端口�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='R';
 send_buffer[6]='P';
 send_buffer[7]='T';
 send_buffer[8]=',';
 send_buffer[9]=num1+48;
 send_buffer[10]=num2+48;
 send_buffer[11]=num3+48;
 send_buffer[12]=num4+48;
 send_buffer[13]=',';
 send_buffer[14]=CRC8_Table(send_buffer, 10);//CRC;
 send_buffer[15]=',';
 send_buffer[16]=0x0D;
 send_buffer[17]=0x0A;
 UART2_SendString(send_buffer,18);
  
}
void RS232_command17()//查询软件版本�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='V';
 send_buffer[5]='E';
 send_buffer[6]='R'; 
 send_buffer[7]=',';
 send_buffer[8]=CRC8_Table(send_buffer, 8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,12);
  
}
void RS232_command18()//恢复出厂参数
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='R';
 send_buffer[5]='P';
 send_buffer[6]='M'; 
 send_buffer[7]=',';
 send_buffer[8]=CRC8_Table(send_buffer, 8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,12);
  
}
 void RS232_command19()//重启控制�?
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='R';
 send_buffer[5]='S';
 send_buffer[6]='T'; 
 send_buffer[7]=','; 
 send_buffer[8]=CRC8_Table(send_buffer, 8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,14);
  
}
void RS232_command20()//读取TCPIP设置
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='R';
 send_buffer[5]='T';
 send_buffer[6]='C'; 
 send_buffer[7]='P';
 send_buffer[8]=',';
 send_buffer[9]=CRC8_Table(send_buffer, 9);//CRC;
 send_buffer[10]=',';
 send_buffer[11]=0x0D;
 send_buffer[12]=0x0A;
 UART2_SendString(send_buffer,13);
  
}
void RS232_command21()//获取报警信息
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='G';
 send_buffer[5]='L';
 send_buffer[6]='E'; 
 send_buffer[7]=',';
 send_buffer[8]=CRC8_Table(send_buffer,8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,12);
  
}
void RS232_command35()//清除报警信息
{
 
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='C';
 send_buffer[5]='L';
 send_buffer[6]='E'; 
 send_buffer[7]=',';
 send_buffer[8]=CRC8_Table(send_buffer,8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,12);
  
}
void RS232_command36()//保存操作
{
 send_buffer[0]='V';
 send_buffer[1]='D';
 send_buffer[2]='C';
 send_buffer[3]=',';
 send_buffer[4]='S';
 send_buffer[5]='A';
 send_buffer[6]='V'; 
 send_buffer[7]=',';
 send_buffer[8]=CRC8_Table(send_buffer,8);//CRC;
 send_buffer[9]=',';
 send_buffer[10]=0x0D;
 send_buffer[11]=0x0A;
 UART2_SendString(send_buffer,12);

}
void RS232_commandOK()
{
 send_buffer[0]='O';
 send_buffer[1]='K';
 send_buffer[2]=0x0D;
 send_buffer[3]=0x0A;

  UART2_SendString(send_buffer,4);
}

void RS232_commandRST()
 {
   send_buffer[0]='V';
   send_buffer[1]='D';
   send_buffer[2]='C';
   send_buffer[3]=',';
   send_buffer[4]='R';
   send_buffer[5]='S';
   send_buffer[6]='T';
   send_buffer[7]=',';
   send_buffer[8]=CRC8_Table(send_buffer,8);//CRC;
   send_buffer[9]=',';
   send_buffer[10]=0x0D;
   send_buffer[11]=0x0A;
   
    UART2_SendString(send_buffer,12);
 }
