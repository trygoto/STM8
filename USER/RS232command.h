#ifndef  __RS232command_H
#define  __RS232command_H
#include"stm8s.h"
#include"task.h"

/*************************************************  
 Copyright ? Linkhou robot Co., Ltd. 2017-2018. All rights reserved.    
 File name: RS232command.h  
 Author: rexvan 
 ID��1606003      
 Version: V2.0       
 Date:2017/11/21 9:43:04   
 Description: Controller panel                  		           
 Others:          
 History:                      
		Date: 2017/11/21 9:43:04          
		Author: rexvan   
		ID: 1606003       
		Modification: rexvan
 *************************************************/
//�������
void CodeSave();
//�������
void CodeClear();
//������ѹģʽ����
void CodeP001Set(int chx,int VoltageCurrent);
//������ѹģʽ��ȡ
void CodeP001Rad(int chx);
//�����������
void CodeP002Set(int chx,int Current);
//��ȡ�������
void CodeP002Rad(int chx);
//�ر�ͨ�����
void CodeP003004(int chx);
//���������ѹ
void CodeP003Set(int chx,int Voltage);
//��ȡ�����ѹ
void CodeP003Rad(int chx);
//���������ѹPWM
void CodeP004Set(int chx,int VoltagePWM);
//��ȡ�����ѹPWM
void CodeP004Rad(int chx);
//����Ƶ������
void CodeP005Set(int chx,int PulseWidth);
//��ѯƵ������
void CodeP005Red(int chx);
//����ͨ��Ĭ�����ģʽ
void CodeP006Set(int chx,int Value);
//��ѯͨ��Ĭ�����ģʽ
void CodeP006Red(int chx);
//�����ⲿIO�ӿڵĹ���ģʽ
void CodeP007Set(int chx,int Mode);
//��ѯ�ⲿIO�ӿڵĹ���ģʽ
 void CodeP007Rad(int chx);
//�����ⲿ���IO�ӿڵĹ���ģʽ
void CodeP008Set(int chx,int Mode);
//��ѯ�ⲿ���IO�ӿڵĹ���ģʽ
void CodeP008Red(int chx);
//��ѯ����IO��ƽ״̬
void CodeP009Red();
//�������IO״̬
void CodeP010Set(int Value[]);
//��ѯ���IO״̬
void CodeP010Rad();
//��ѯ�������¶�
void CodeP011Red();
//���ô��ڲ�����
void CodeP012Set(int Value);
//��ȡ���ڲ�����
void CodeP012Red();
//���ÿ�����IP��ַ
void CodeP013Set(int Value[]);
//��ȡ������IP��ַ
void CodePIPRea();
//������������
void CodeP014Set(int Value[]);












#endif


