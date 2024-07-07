/***************************************************************************
实验名称： PS2键盘读取实验

实验模块:  51单片机核心板、液晶显示区、鼠标键盘接口

实验接线： 51单片机核心板------鼠标键盘接口
				P3.2--------------SDA
				P3.3--------------SLK
				
			51单片机核心板------液晶显示区
				 P3.0--------------RS
				 P3.1--------------RW
				 P3.2--------------E
			P0.0~P0.7--------------DB0~DB7
						
现象描述：按下键盘的按键，1602下排显示按下的按键的键值

更新时间：2017.10.17
***************************************************************************/

#include <Reg52.h>	
#include <stdio.h>

sbit  LCM_RS = P2^0; //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80    //用于检测LCM状态字中的Busy标识

sbit Key_Data =P3^2; //定义Keyboard引脚
sbit Key_CLK=  P3^3;

unsigned char code Welcome[] = {"PC_KEYboard_test"};
unsigned char code Tips[] = {"Press__any__key."};
unsigned char code Cls[] = {" "};
static unsigned char IntNum = 0; //中断次数计数
static unsigned char KeyV;       //键值
static unsigned char DisNum = 0; //显示用指针
static unsigned char Key_UP=0, Shift = 0;//Key_UP是键松开标识，Shift是Shift键按下标识
static unsigned char BF = 0;     //标识是否有字符被收到

unsigned char code UnShifted[59][2] = {
0x1C, 'a',
0x32, 'b',
0x21, 'c',
0x23, 'd',
0x24, 'e',
0x2B, 'f',
0x34, 'g',
0x33, 'h',
0x43, 'i',
0x3B, 'j',
0x42, 'k',
0x4B, 'l',
0x3A, 'm',
0x31, 'n',
0x44, 'o',
0x4D, 'p',
0x15, 'q',
0x2D, 'r',
0x1B, 's',
0x2C, 't',
0x3C, 'u',
0x2A, 'v',
0x1D, 'w',
0x22, 'x',
0x35, 'y',
0x1A, 'z',
0x45, '0',
0x16, '1',
0x1E, '2',
0x26, '3',
0x25, '4',
0x2E, '5',
0x36, '6',
0x3D, '7',
0x3E, '8',
0x46, '9',
0x0E, '`',
0x4E, '-',
0x55, '=',
0x5D, '\\',
0x29, ' ',
0x54, '[',
0x5B, ']',
0x4C, ';',
0x52, '\'',
0x41, ',',
0x49, '.',
0x4A, '/',
0x71, '.',
0x70, '0',
0x69, '1',
0x72, '2',
0x7A, '3',
0x6B, '4',
0x73, '5',
0x74, '6',
0x6C, '7',
0x75, '8',
0x7D, '9',
};

unsigned char code Shifted[59][2] = {
0x1C, 'A',
0x32, 'B',
0x21, 'C',
0x23, 'D',
0x24, 'E',
0x2B, 'F',
0x34, 'G',
0x33, 'H',
0x43, 'I',
0x3B, 'J',
0x42, 'K',
0x4B, 'L',
0x3A, 'M',
0x31, 'N',
0x44, 'O',
0x4D, 'P',
0x15, 'Q',
0x2D, 'R',
0x1B, 'S',
0x2C, 'T',
0x3C, 'U',
0x2A, 'V',
0x1D, 'W',
0x22, 'X',
0x35, 'Y',
0x1A, 'Z',
0x45, '0',
0x16, '1',
0x1E, '2',
0x26, '3',
0x25, '4',
0x2E, '5',
0x36, '6',
0x3D, '7',
0x3E, '8',
0x46, '9',
0x0E, '~',
0x4E, '_',
0x55, '+',
0x5D, '|',
0x29, ' ',
0x54, '{',
0x5B, '}',
0x4C, ':',
0x52, '"',
0x41, '<',
0x49, '>',
0x4A, '?',
0x71, '.',
0x70, '0',
0x69, '1',
0x72, '2',
0x7A, '3',
0x6B, '4',
0x73, '5',
0x74, '6',
0x6C, '7',
0x75, '8',
0x7D, '9',
};

/**********************************************************/
/*******************LCM1602相关函数************************/
/**********************************************************/
//读状态
////////////////////////////////////////////////////////////////////////////
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF; 
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    while (LCM_Data & Busy); //检测忙信号
    return(LCM_Data);
    LCM_E = 0;
}


/**********************************************************/
//5ms延时
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

/**********************************************************/
//写数据
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //检测忙
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; //若晶振速度太高可以在这后加小的延时
    LCM_E = 0; //延时
    LCM_E = 1;
    LCM_E = 0;
}

/**********************************************************/
//写指令
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
    if (BuysC) ReadStatusLCM(); //根据需要检测忙
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0; 
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1; 
    LCM_E = 0;
}

/**********************************************************/
//读数据
unsigned char ReadDataLCM(void)
{
    LCM_RS = 1; 
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    return(LCM_Data);
    LCM_E = 0;
}

/**********************************************************/
//LCD数据指针位置程序
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//数据指针=80+地址码(00H~27H,40H~67H)
}

void LCMInit(void) //LCM初始化
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 

    WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
    WriteCommandLCM(0x08,1); //关闭显示
    WriteCommandLCM(0x01,1); //显示清屏
    WriteCommandLCM(0x06,1); // 显示光标移动设置
    WriteCommandLCM(0x0C,1); // 显示开及光标设置
}

/**********************************************************/
//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF; //限制X不能大于15，Y不能大于1
    if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
    X |= 0x80; //算出指令码
    WriteCommandLCM(X, 0); //这里不检测忙信号，发送地址码
    WriteDataLCM(DData);
}

////////////////////////////////////////////////////////////////////////////
//按指定位置显示一串字符
////////////////////////////////////////////////////////////////////////////
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
    unsigned char ListLength;

    ListLength = 0;
    Y &= 0x1;
    X &= 0xF; //限制X不能大于15，Y不能大于1
    while (DData[ListLength]>0x20) //若到达字串尾则退出
    {
        if (X <= 0xF) //X坐标应小于0xF
        {
            DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
            ListLength++;
            X++;
        }
    }
}

/**********************************************************/

void Keyboard_out(void) interrupt 2
{
    if ((IntNum > 0) && (IntNum < 9))
        { 
            KeyV = KeyV >> 1; //因键盘数据是低>>高，结合上一句所以右移一位
            if (Key_Data) KeyV = KeyV | 0x80; //当键盘数据线为1时为1到最高位
        }
    IntNum++;
    while (!Key_CLK); //等待PS/2CLK拉高

    if (IntNum > 10)
        {
            IntNum = 0; //当中断11次后表示一帧数据收完，清变量准备下一次接收
            BF = 1; //标识有字符输入完了
            EA = 0; //关中断等显示完后再开中断 (注：如这里不用BF和关中断直接调Decode()则所Decode中所调用的所有函数要声明为再入函数)
        }
}

void Decode(unsigned char ScanCode) //注意:如SHIFT+G为12H 34H F0H 34H F0H 12H，也就是说shift的通码+G的通码+shift的断码+G的断码
{
    unsigned char TempCyc; 

    if (!Key_UP) //当键盘松开时
        {
            switch (ScanCode)
                {
                    case 0xF0 : // 当收到0xF0，Key_UP置1表示断码开始
                            Key_UP = 1;
                            break;

                    case 0x12 : // 左 SHIFT
                            Shift = 1;
                            break;

                    case 0x59 : // 右 SHIFT
                            Shift = 1;
                            break;

                    default: 
                    if (DisNum > 15)
                        {
                            DisplayListChar(0, 1, Cls);//清LCD第二行
                            DisNum = 0; 
                        }
                    if(!Shift) //如果SHIFT没按下
                        {
                            for (TempCyc = 0;(UnShifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
                            if (UnShifted[TempCyc][0] == ScanCode) DisplayOneChar(DisNum, 1, UnShifted[TempCyc][1]);
                            DisNum++;
                        } 
                    else //按下SHIFT
                        {
                            for(TempCyc = 0; (Shifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
                            if (Shifted[TempCyc][0] == ScanCode) DisplayOneChar(DisNum, 1, Shifted[TempCyc][1]);
                            DisNum++;
                        }

                    break;
                }
        }
        else
            { 
                Key_UP = 0;
                switch (ScanCode) //当键松开时不处理判码，如G 34H F0H 34H 那么第二个34H不会被处理
                    {
                        case 0x12 : // 左 SHIFT
                            Shift = 0;
                            break;

                        case 0x59 : // 右 SHIFT
                            Shift = 0;
                            break;
                    }
            }
        BF = 0; //标识字符处理完了
}

void main(void)
{
    unsigned char TempCyc;

    LCMInit(); //LCM初始化 
    DisplayListChar(0, 0, Welcome);
    DisplayListChar(0, 1, Tips);
    ReadDataLCM();//测试用句无意义
    for (TempCyc=0; TempCyc<10; TempCyc++)
    Delay5Ms(); //延时
    DisplayListChar(0, 1, Cls); 

    IT1 = 0; //设外部中断1为低电平触发
    EA = 1;
    EX1 = 1; //开中断

    while(1)
        {
            if (BF)
            Decode(KeyV);
            else
            EA = 1; //开中断
        }
} 
