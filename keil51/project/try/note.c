#include<REGX52.H>
#include<stdarg.h>
void Timer_Init(){

}

void Int0_Routine(void) interrupt 0 {
    TCON &= 0xF0;//����������һ��Ϊһ
    TCON |= 0x01;//�����������Ϊ��

    
}