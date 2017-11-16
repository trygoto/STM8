#ifndef  __RS232command_H
#define  __RS232command_H


#include"stm8s.h"
#include"task.h"


void CodeP001Set(int chx,int VoltageCurrent);
void CodeP001Rad(int chx,int VoltageCurrent);




void RS232_command1(int num);
void RS232_command2(int num);
void RS232_command3(int num);
void RS232_command4(int num);
void RS232_command5(int num);
void RS232_command6(int num);
void RS232_command7();
void RS232_command8( );
void RS232_command9( );
void RS232_command10(int num );
void RS232_command11(int num1,int num2,int num3,int num4 );
void RS232_command12(int num1,int num2,int num3,int num4 );
void RS232_command13(int num1,int num2,int num3,int num4 );
void RS232_command14(int num1,int num2,int num3,int num4 );
void RS232_command15(int num1,int num2,int num3,int num4 );
void RS232_command16();
void RS232_command17();
void RS232_command18();
void RS232_command19();
void RS232_command20();
void RS232_command21();
void RS232_command22(int num1,int num2,int num3,int num4);
void RS232_command23(int num1,int num2,int num3,int num4,int num5);
void RS232_command24(int num1,int num2);//设置电压
void RS232_command25(int num1,int num2);//设置外部触发方式
void RS232_command26(int num1,int num2);//设置通道默认输出模式
void RS232_command27(int num1,int num2);//设置外部IO接口工作模式
void RS232_command34(int num1,int num2,int num3,int num4,int num5);
void RS232_command35();
void RS232_command36();//保存操作
void RS232_commandOK();
void RS232_commandRST();
#endif


