#include <wiringPi.h>
#include <stdio.h>

#define pin 7

int main()
{
    int cmd;
    if (wiringPiSetup() == -1)
    {
        printf("init failt!!!\n");
        return -1;
    }
    pinMode(pin, OUTPUT);    // 输出模式
    digitalWrite(pin, HIGH); // pin引脚输出高电平

    while (1)
    {
        printf("input 0 or 1:\n");
        scanf("%d", &cmd);
        // getchar();
        if (cmd == 0)
        {
            printf("output low\n\n");
            digitalWrite(pin, LOW); // pin引脚输出低电平
        }
        else if (cmd == 1)
        {
            printf("output high\n\n");
            digitalWrite(pin, HIGH); // pin引脚输出高电平
        }
        else
        {
            printf("input error\n\n");
        }
    }
    return 0;
}
