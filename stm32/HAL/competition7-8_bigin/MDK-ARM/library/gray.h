#ifndef  _GRAY__H_
#define  _GRAY__H_

#include "main.h"
#include "drive.h"
#include "pid.h"
#define L1_PORT GPIOE
#define L1_PIN  GPIO_PIN_2

#define L2_PORT GPIOE
#define L2_PIN  GPIO_PIN_4

#define L3_PORT GPIOE
#define L3_PIN  GPIO_PIN_6

#define M_PORT GPIOC
#define M_PIN  GPIO_PIN_0

#define R1_PORT GPIOC
#define R1_PIN  GPIO_PIN_13

#define R2_PORT GPIOE
#define R2_PIN  GPIO_PIN_5

#define R3_PORT GPIOE
#define R3_PIN  GPIO_PIN_3

uint8_t SCAN_ground(void);
//uint8_t xunji(void);
extern int16_t l_speed,r_speed,base_speed;
extern uint8_t L1,L2,L3,M,R1,R2,R3;

extern uint32_t result;

#endif
