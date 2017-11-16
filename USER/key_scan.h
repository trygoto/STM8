

#ifndef  __KEY_SCAN_H
#define  __KEY_SCAN_H
#include "stm8s_gpio.h"

#define uint  unsigned int
#define uchar  unsigned char
#define N_key    0             //无键 
#define S_key    1             //单键  
#define D_key    2             //双键  
#define L_key    3             //长键 
#define key_state_0 0  
#define key_state_1 1  
#define key_state_2 2 
#define key_state_3 3 
extern u8 key;
extern u8 short_key;
extern u8 double_key;
extern u8 long_key;


#define CodingsWitch_A   GPIO_ReadInputPin(GPIOA,GPIO_PIN_6)//
#define CodingsWitch_B   GPIO_ReadInputPin(GPIOA,GPIO_PIN_5)//

#define SW02_ON   0
#define SW02_OFF  1

#define SW02  GPIO_ReadInputPin(GPIOE,GPIO_PIN_5)



void KEY_Init(void);
unsigned char key_driver(void);
unsigned char key_read(void) ;
int key_EC11(u8 limit);
void CodingsWitchPollint();

#endif