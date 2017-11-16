#ifndef  _seg_H
#define  _seg_H

#include"stm8s.h"
#define SMG_weinum 5

#define seg_a             (1<<0)
#define seg_b             (1<<1)
#define seg_c             (1<<2)
#define seg_d             (1<<3)
#define seg_e             (1<<2)
#define seg_f             (1<<3)
#define seg_g             (1<<6)
#define seg_dp            (1<<7)

#define seg_wei1          (1<<2)
#define seg_wei2          (1<<3)
#define seg_wei3          (1<<4)
#define seg_wei4          (1<<5)
#define seg_wei5          (1<<6)



#define seg_a_GPIO        GPIOB
#define seg_b_GPIO        GPIOB
#define seg_c_GPIO        GPIOB
#define seg_d_GPIO        GPIOB
#define seg_e_GPIO        GPIOD
#define seg_f_GPIO        GPIOD
#define seg_g_GPIO        GPIOB
#define seg_dp_GPIO       GPIOB

#define seg_wei1_GPIO     GPIOC
#define seg_wei2_GPIO     GPIOC
#define seg_wei3_GPIO     GPIOC
#define seg_wei4_GPIO     GPIOC
#define seg_wei5_GPIO     GPIOC

void seg_Init(void);


void SW02Init(void);
void key_scan(void);
void display(u8 a1,u8 a2,u8 a3,u8 a4,u8 a5);
void display1(u8 a1,u8 a2,u8 a3,u8 a4,u8 a5,u8 a6);
void smxs(void);

void smg_l(u8 a);
void smg_write(u8 a);
void smgqp(void);
void delay(u32 nCount);


#endif
