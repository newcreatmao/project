#include <reg52.h>
#include <intrins.h>
void Delay100ms()        //@12.000MHz
{
    unsigned char data i, j, k;

    _nop_();
    _nop_();
    i = 5;
    j = 144;
    k = 71;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

void main()
{
    P1=0xff;
    while(1)
    {
        int i=0;
        for(i=0;i<8;i++){
            P1=~(0x01<<i);
            Delay100ms();
        }
        for(;i>0;i--){
            P1=~(0x01<<i);
            Delay100ms();
        }
}
    }