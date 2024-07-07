#include<REGX52.H>
#include<stdarg.h>
void Timer_Init(){

}

void Int0_Routine(void) interrupt 0 {
    TCON &= 0xF0;//并，两个是一才为一
    TCON |= 0x01;//或，两个是零才为零

    
}