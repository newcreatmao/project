#include <reg52.H>

char string[20];
unsigned char tmp;
char code st[] = "string";
char code nu[] = "int";
char code fl[] = "float";
bit flag_st = 0; 
bit flag_ed = 0;
bit flag_point = 0, flag_str = 0, flag_num = 0; 
sbit    KEY = P1^0;

void Delay(unsigned int xms)        
{
    unsigned char i, j;
    while(xms)
    {
    i = 2;
    j = 239;
    do
    {
        while (--j);
    } while (--i);
    xms--;
    }
}

void UART_init()
{
    TMOD = 0x20;        // ???1???8??????????, ???????
    TH1 = 0xFD;            // ???9600
    TL1 = 0xFD;    
    SCON = 0x50;        // ?????????
    PCON &= 0xef;        // ??????        
    TR1 = 1;            // ?????1
    IE = 0x0;            // ??????
}

void send_str(char *s)       
{
    unsigned char i = 0;
    while(s[i] != '\0')
    {
        SBUF = s[i];
        while(!TI);                // ??????
        TI = 0;                    // ????????
        i++;                     // ?????
    }
}


void proc_key(){
    int tmp = 0;    
    if(KEY == 0){           
        if(flag_point == 1 && flag_str == 0 && flag_num==1)     
            send_str(fl);
        else if(flag_point == 0 && flag_num== 1 && flag_str == 0) 
            send_str(nu);
        else if(flag_str == 1) 
            send_str(st);
    }
    flag_point = 0;
    flag_str = 0;
    flag_num = 0;
}

void main()
{
    unsigned char i = 0;
    int stt = 0;
    unsigned char type = 0;    
    
  UART_init();     
    while(1)
    {
        if(KEY == 0)                // ????
        {
            Delay(10);                // ?????
            if(KEY == 0)            // ????
                proc_key();           // ???
        }
        if(RI){                                   // ???????
            RI = 0;
            tmp = SBUF;                   // ????????
            if (tmp == '('){
                flag_st = 1;
                flag_ed=0;
            }
            if (tmp == ')'){
                flag_st = 1;
                flag_ed=1;
            }
            if(flag_st == 1 && flag_ed == 0){
                if (tmp != '(' && tmp != ')' && stt < 19){
                    string[stt] = tmp;
                    stt++;
                    if(tmp == '.'&&flag_point!=1)
                        flag_point = 1;
                    else if(tmp >= '0' && tmp <= '9') 
                        flag_num = 1;
                    else if(tmp == '(' || tmp == ')') {;}
                    else flag_str = 1;
                }    
            }
            if(flag_st == 1 && flag_ed == 1)
            {
                string[stt+1] = '\0';
                stt = 0;
                flag_st = 0;
                flag_ed=0;
            }
        }
    }
}