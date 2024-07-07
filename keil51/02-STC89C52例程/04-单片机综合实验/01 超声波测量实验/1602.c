
/******************硬件接口************************/
#define LCD_DATA P0        //LCD的数据口
sbit LCD_BUSY=LCD_DATA^7;  //LCD忙信号位
sbit LCD_RW=P2^1;          //LCD读写控制
sbit LCD_RS=P2^0;          //LCD寄存器选择
sbit LCD_EN=P2^2;        //LCD使能信号
unsigned char dis[20];
#define DE 2

#define OFF_DISPLAY   LCD_write_instruction(0x08); //关掉显示
#define OPEN_DISPLAY  LCD_write_instruction(0x0c); //开显示
#define CLAERN_DISPLAY  LCD_write_instruction(0x01);//清屏指令


/****************************************************/
void Delay(unsigned int time)
{
  while(time--);
}
/****************************************************/
void LCD_check_busy(void)  //检测LCD状态，看它是不是还在忙呢
{
while(1)
{
LCD_EN=0;
LCD_RS=0; //指令寄存器通信
LCD_RW=1;  //read data
LCD_DATA=0xff;
LCD_EN=1;
Delay(DE);
if(!LCD_BUSY)break;
}
LCD_EN=0;
}
/****************************************************/
void LCD_write_instruction(unsigned char LCD_instruction)  //写指令到LCD
{
LCD_check_busy();
LCD_RS=0;
LCD_RW=0; //写数据
LCD_DATA=LCD_instruction;
LCD_EN=1;
Delay(DE);
LCD_EN=0;
}
/****************************************************/
void LCD_write_data(unsigned char LCD_data)      //输出一个字节数据到LCD
{
LCD_check_busy();
LCD_RS=1;
LCD_RW=0;
LCD_DATA=LCD_data;
LCD_EN=1;
Delay(DE);
LCD_EN=0;
}

/*****************************************************/
void DispStrPosi(unsigned char *str, unsigned char posi, unsigned char row)
{
unsigned char ch;
unsigned char i = 0;

if(row > 1)
 return; 
if(row == 1)
ch = 0xc0+posi;
else
 ch = 0x80+posi;
while(*str != 0)
{
LCD_write_instruction(ch + i);
LCD_write_data(*str++);
i++;
}}
/****************************************************/
void LCD_init()
{
   LCD_write_instruction(0x3c);  //  8bit wire  2 line 5*10 dot
   Delay(1000);           // delay 50us
   LCD_write_instruction(0x0c);  // open display  close cursor
   Delay(1000);
   LCD_write_instruction(0x01);  // clear display
   Delay(1000);
   LCD_write_instruction(0x06);  // entry mode set 
}


    
