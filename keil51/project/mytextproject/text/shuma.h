#include <REGX52.h>
#include "delay.h"
#include "color.h"

extern unsigned char DS1302_Time[];
extern unsigned char test_show1;

/*
sbit IA = P2^2;
sbit IB = P2^3;
void show_pos();
void show_num();
void nixie_show(char pos,char num);
*/


void towtoten(unsigned char location,unsigned char *x);
void children(unsigned char location,number);//定义子函数
void light_four(unsigned char a[]);
void ymd();
void hms();
void ad(unsigned int Data);
