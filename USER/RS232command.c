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
//�������
void CodeSave()
{
	gmemcpy(send_buffer,"IDC,SAV,?,\r\n",12);	
	send_buffer[8]=CRC8_Table(send_buffer, 8);
	UART2_SendString(send_buffer,12);

}
//�������
void CodeClear()
{
	gmemcpy(send_buffer,"IDC,CLE,?,\r\n",12);	
	send_buffer[8]=CRC8_Table(send_buffer, 8);
 	UART2_SendString(send_buffer,12);
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
	gmemcpy(send_buffer,"IDC,OSLI,1,0012,?,\r\n",20);
	send_buffer[9]=chx+'0';
	send_buffer[11]=((Current/1000)%10)+'0';
	send_buffer[12]=((Current/100)%10)+'0';
	send_buffer[13]=((Current/10)%10)+'0';
	send_buffer[14]=(Current%10)+'0';
	send_buffer[16]=CRC8_Table(send_buffer, 16);
	UART2_SendString(send_buffer,20);

}
//��ȡ�������
void CodeP002Rad(int chx)
{
	gmemcpy(send_buffer,"IDC,GLI,1,?,\r\n",14);
 	send_buffer[8]=chx+'0';
	
	send_buffer[10]=CRC8_Table(send_buffer, 10);
 	UART2_SendString(send_buffer,14);	

}

//���������ѹ
void CodeP003Set(int chx,int Voltage)
{

	gmemcpy(send_buffer,"IDC,OSVOT,1,123,?,\r\n",20);
 	send_buffer[10]=chx+'0';
	
 	send_buffer[12]=((Voltage/100)%10)+'0';
	send_buffer[13]=((Voltage/10)%10)+'0';
	send_buffer[14]=(Voltage%10)+'0';
	
	send_buffer[16]=CRC8_Table(send_buffer, 16);
 	UART2_SendString(send_buffer,20);	
}

//��ȡ�����ѹ
void CodeP003Rad(int chx)
{
 	gmemcpy(send_buffer,"IDC,GVOT,1,?,\r\n",15);
	send_buffer[9]=chx+'0';

	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);	
}
//�ر�ͨ��
void CodeP003004(int chx)
{
	gmemcpy(send_buffer,"IDC,CLS,1,?,\r\n",14);
 	send_buffer[8]=chx+'0';
	
	send_buffer[10]=CRC8_Table(send_buffer, 10);
 	UART2_SendString(send_buffer,14);	

}

//���������ѹPWM
void CodeP004Set(int chx,int VoltagePWM)
{

	gmemcpy(send_buffer,"IDC,OSPWM,1,123,?,\r\n",20);
 	send_buffer[10]=chx+'0';
	
 	send_buffer[12]=((VoltagePWM/100)%10)+'0';
	send_buffer[13]=((VoltagePWM/10)%10)+'0';
	send_buffer[14]=(VoltagePWM%10)+'0';
	
	send_buffer[16]=CRC8_Table(send_buffer, 16);
 	UART2_SendString(send_buffer,20);	
}

//��ȡ�����ѹPWM
void CodeP004Rad(int chx)
{
 	gmemcpy(send_buffer,"IDC,GPWM,1,?,\r\n",15);
	send_buffer[9]=chx+'0';

	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);	
}

//����Ƶ������
void CodeP005Set(int chx,int PulseWidth)
{
	gmemcpy(send_buffer,"IDC,STR,1,0120,?,\r\n",19);
	send_buffer[8]=chx+'0';

	send_buffer[10]=((PulseWidth/1000)%10)+'0';
	send_buffer[11]=((PulseWidth/100)%10)+'0';
	send_buffer[12]=((PulseWidth/10)%10)+'0';
	send_buffer[13]=(PulseWidth%10)+'0';

	
	send_buffer[15]=CRC8_Table(send_buffer, 15);
	UART2_SendString(send_buffer,19);	

}
//��ѯƵ������

void CodeP005Red(int chx)
{

	gmemcpy(send_buffer,"IDC,GTR,3,?,\r\n",14);
	send_buffer[8]=chx+'0';

	send_buffer[10]=CRC8_Table(send_buffer, 10);
	UART2_SendString(send_buffer,14);	

}

//����ͨ��Ĭ�����ģʽ
void CodeP006Set(int chx,int Value)
{

	gmemcpy(send_buffer,"IDC,SMOUT,1,1,?,\r\n",18);
	send_buffer[10]=chx+'0';

	send_buffer[12]=Value+'0';

	send_buffer[14]=CRC8_Table(send_buffer, 14);
	UART2_SendString(send_buffer,18);		

}
//��ѯͨ��Ĭ�����ģʽ
void CodeP006Red(int chx)
{
	gmemcpy(send_buffer,"IDC,GMOUT,1,?,\r\n",16);
	send_buffer[10]=chx+'0';

	send_buffer[12]=CRC8_Table(send_buffer, 12);
	UART2_SendString(send_buffer,16);		

}

//�����ⲿ����IO�ӿڵĹ���ģʽ
void CodeP007Set(int chx,int Mode)
{
	gmemcpy(send_buffer,"IDC,SIOIM,1,1,?,\r\n",18);
	send_buffer[10]=chx+'0';
	send_buffer[12]=Mode+'0';

	send_buffer[14]=CRC8_Table(send_buffer, 14);
	UART2_SendString(send_buffer,18);
}

//��ѯ�ⲿ����IO�ӿڵĹ���ģʽ
 void CodeP007Rad(int chx)
{
	gmemcpy(send_buffer,"IDC,GIOIM,1,?,\r\n",16);
	send_buffer[10]=chx+'0';

	send_buffer[12]=CRC8_Table(send_buffer, 12);
	UART2_SendString(send_buffer,16);

}

//�����ⲿ���IO�ӿڵĹ���ģʽ
void CodeP008Set(int chx,int Mode)
 {
 
	 gmemcpy(send_buffer,"IDC,SIOOM,1,1,?,\r\n",18);
	 send_buffer[10]=chx+'0';
	 send_buffer[12]=Mode+'0';

	 
	 send_buffer[14]=CRC8_Table(send_buffer, 14);
	 UART2_SendString(send_buffer,18);

}

//��ѯ�ⲿ���IO�ӿڵĹ���ģʽ
void CodeP008Red(int chx)
{
	gmemcpy(send_buffer,"IDC,GIOOM,1,?,\r\n",16);
	send_buffer[10]=chx+'0';
	
	send_buffer[12]=CRC8_Table(send_buffer, 12);
	UART2_SendString(send_buffer,16);

}

//��ѯ����IO��ƽ״̬
void CodeP009Red()
{

	gmemcpy(send_buffer,"IDC,IORBIT,?,\r\n",15);

	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);
}

//�������IO״̬
void CodeP010Set(int Value[])
{
	gmemcpy(send_buffer,"IDC,IOWBIT,00000,?,\r\n",21);

	send_buffer[11]=Value[0]+'0';
	send_buffer[12]=Value[1]+'0';
	send_buffer[13]=Value[2]+'0';
	send_buffer[14]=Value[3]+'0';
	send_buffer[15]=Value[4]+'0';

	
	send_buffer[17]=CRC8_Table(send_buffer, 17);
	UART2_SendString(send_buffer,21);		
}

//��ѯ���IO״̬
void CodeP010Rad()
{
	gmemcpy(send_buffer,"IDC,IOGRBIT,?,\r\n",16);
	
	send_buffer[12]=CRC8_Table(send_buffer, 12);
	UART2_SendString(send_buffer,16);

}

//��ѯ�������¶�
void CodeP011Red()
{
	gmemcpy(send_buffer,"IDC,GTEM,?,\r\n",13);
	
	send_buffer[9]=CRC8_Table(send_buffer, 9);
	UART2_SendString(send_buffer,13);	

}

//���ô��ڲ�����
void CodeP012Set(int Value)
{

	gmemcpy(send_buffer,"IDC,SBTL,1,?,\r\n",15);

	send_buffer[9]=Value+'0';
	
	send_buffer[11]=CRC8_Table(send_buffer, 11);
	UART2_SendString(send_buffer,15);	



}
//��ȡ���ڲ�����
void CodeP012Red()
{
	gmemcpy(send_buffer,"IDC,GBTL,?,\r\n",13);
		
	send_buffer[9]=CRC8_Table(send_buffer, 9);
	UART2_SendString(send_buffer,13);	

}

//���ÿ�����IP��ַ
void CodeP013Set(int Value[])
{

	int i=0;
	int temp=9;
	gmemcpy(send_buffer,"IDC,SLIP,192,168,001,100,?,\r\n",29);

	for(;i<4;i++)
	{
		send_buffer[temp++]=((Value[i]/100)%10)+'0';
		send_buffer[temp++]=((Value[i]/10)%10)+'0';
		send_buffer[temp++]=(Value[i]%10)+'0';
		temp++;
	}

	send_buffer[25]=CRC8_Table(send_buffer, 25);
	UART2_SendString(send_buffer,29);
}

//��ȡ������IP��ַ
void CodePIPRea()
{
	gmemcpy(send_buffer,"IDC,RTCP,?,\r\n",13);
			
	send_buffer[9]=CRC8_Table(send_buffer, 9);
	UART2_SendString(send_buffer,13);	

}

//������������
void CodeP014Set(int Value[])
{

	int i=0;
	int temp=8;
	gmemcpy(send_buffer,"IDC,SNM,192,168,001,100,?,\r\n",28);

	for(;i<4;i++)
	{
		send_buffer[temp++]=((Value[i]/100)%10)+'0';
		send_buffer[temp++]=((Value[i]/10)%10)+'0';
		send_buffer[temp++]=(Value[i]%10)+'0';
		temp++;
	}

	send_buffer[24]=CRC8_Table(send_buffer, 24);
	UART2_SendString(send_buffer,28);
}








