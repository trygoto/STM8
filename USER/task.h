#ifndef  _task_H
#define  _task_H
#include"stm8s.h"

/*************************************************  
 Copyright ? Linkhou robot Co., Ltd. 2017-2018. All rights reserved.    
 File name: task.h  
 Author: rexvan 
 ID£º1606003      
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

extern bool teplet;
extern bool mode_flag;

int key_NUM(void);
void HELL_SHOW(void);
void LH_RUN();
void SAVE();
void YES();
void ERR0();
void P_XX();
void P_001();
void P_002();
void P_003();
void P_004();
void P_005();
void P_006();
void P_007();
void P_008();
void P_009();
void P_010();
void P_011();
void P_012();
void P_013();
void P_014();
void P_015();
void P_016();
void P_017();
void P_018();
void P_019();
void P_020();
#endif