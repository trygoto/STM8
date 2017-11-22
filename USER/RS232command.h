#ifndef  __RS232command_H
#define  __RS232command_H
#include"stm8s.h"
#include"task.h"

/*************************************************  
 Copyright ? Linkhou robot Co., Ltd. 2017-2018. All rights reserved.    
 File name: RS232command.h  
 Author: rexvan 
 ID：1606003      
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
//保存参数
void CodeSave();
//清除报警
void CodeClear();
//恒流恒压模式设置
void CodeP001Set(int chx,int VoltageCurrent);
//恒流恒压模式读取
void CodeP001Rad(int chx);
//设置输出电流
void CodeP002Set(int chx,int Current);
//读取输出电流
void CodeP002Rad(int chx);
//关闭通道输出
void CodeP003004(int chx);
//设置输出电压
void CodeP003Set(int chx,int Voltage);
//读取输出电压
void CodeP003Rad(int chx);
//设置输出电压PWM
void CodeP004Set(int chx,int VoltagePWM);
//读取输出电压PWM
void CodeP004Rad(int chx);
//设置频闪脉宽
void CodeP005Set(int chx,int PulseWidth);
//查询频闪脉宽
void CodeP005Red(int chx);
//设置通道默认输出模式
void CodeP006Set(int chx,int Value);
//查询通道默认输出模式
void CodeP006Red(int chx);
//设置外部IO接口的工作模式
void CodeP007Set(int chx,int Mode);
//查询外部IO接口的工作模式
 void CodeP007Rad(int chx);
//设置外部输出IO接口的工作模式
void CodeP008Set(int chx,int Mode);
//查询外部输出IO接口的工作模式
void CodeP008Red(int chx);
//查询输入IO电平状态
void CodeP009Red();
//设置输出IO状态
void CodeP010Set(int Value[]);
//查询输出IO状态
void CodeP010Rad();
//查询控制器温度
void CodeP011Red();
//设置串口波特率
void CodeP012Set(int Value);
//读取串口波特率
void CodeP012Red();
//设置控制器IP地址
void CodeP013Set(int Value[]);
//读取控制器IP地址
void CodePIPRea();
//设置子网掩码
void CodeP014Set(int Value[]);












#endif


