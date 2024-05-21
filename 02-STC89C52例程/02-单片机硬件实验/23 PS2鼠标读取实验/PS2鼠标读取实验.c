/***************************************************************************
ʵ�����ƣ� PS2����ȡʵ��

ʵ��ģ��:  51��Ƭ�����İ塢Һ����ʾ����������������������

ʵ����ߣ� 51��Ƭ�����İ�------��������(J29)
				P3.3--------------CLK
				P3.4--------------SDA
				
			51��Ƭ�����İ�------Һ����ʾ��
				 P2.0--------------RS
				 P2.1--------------RW
				 P2.2--------------E
			P0.0~P0.7--------------DB0~DB7
			
			51��Ƭ�����İ�------��������
				P3.7--------------PUL
				
						
����������������꣬1602������ʾ�Ƕ�Ӧ����갴�����¡��������ŷ����������졣

����ʱ�䣺2017.10.17
***************************************************************************/

#include<REG52.H>  
#include "intrins.h"     //_nop_();��ʱ������

sbit mouse_SDA=P3^4;//������P3_4 
sbit mouse_CLK=P3^3;//ʱ����P3_3 

sbit LCD1602_RS=P2^0;
sbit LCD1602_RW=P2^1;  
sbit LCD1602_EN=P2^2;
#define LCM1602_DATA P0

#define CLEARSCREEN LCM1602_write_cmd(0x01) 
 
#define uchar unsigned char 
#define uint unsigned int 

sbit beep=P3^7;
                             
unsigned char bdata mouse_byte; //�����ֽ� 
sbit mouse_byte_bit0=mouse_byte^0;//mouse_byte��0λ 
sbit mouse_byte_bit1=mouse_byte^1;//mouse_byte��1λ 
sbit mouse_byte_bit2=mouse_byte^2;//mouse_byte��2λ 
sbit mouse_byte_bit3=mouse_byte^3;//mouse_byte��3λ 
sbit mouse_byte_bit4=mouse_byte^4;//mouse_byte��4λ 
sbit mouse_byte_bit5=mouse_byte^5;//mouse_byte��5λ 
sbit mouse_byte_bit6=mouse_byte^6;//mouse_byte��6λ 
sbit mouse_byte_bit7=mouse_byte^7;//mouse_byte��7λ 
 
unsigned char bdata mouse_fuction;//������Ϣ�ֽ�  
                       
unsigned char mouse_buffer[11];   //����λ���ݻ����� 
unsigned char mouse_buffer_bit=0; //mouse_buffer[mouse_buffer_bit] 
unsigned char mouse_data[3];      //����������ݻ�����,�ֱ���:������Ϣ�ֽ�,xλ����,yλ���� 
unsigned char mouse_data_bit=0;   //mouse_data[mouse_data_bit] 
 
unsigned int move_x=10000;//��ź����� 
unsigned int move_y=10000;//��������� 

//********************************************************************** 
void LCM1602_Init(void);									//Һ����ʼ�� 
void LCM1602_write_cmd(unsigned char command);		//д���� 
void LCM1602_write_data(unsigned char temp);			//д���� 
void LCM1602_set_xy(unsigned char x, unsigned char y);//�������� 
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat);//дһ���ַ�����x��y�� 
void LCM1602_write_string(unsigned char x,unsigned char y,unsigned char *s);//д�ַ�������x��y�� 
void LCM1602_Read_BF(void);                       //��æ�ź� 
void num(unsigned char x,unsigned char y,unsigned int n);//�ڵ�x��,��y����ʾ��������n 
//********************************************************************** 
////////////////////////////////////////////////////////////////////////////
//LCD��ʼ���ӳ���
////////////////////////////////////////////////////////////////////////////
void LCM1602_Init(void) 
{  
	LCM1602_write_cmd(0x28); 
	LCM1602_write_cmd(0x28); 
	LCM1602_write_cmd(0x28);//����4λ���ݴ���ģʽ 
	LCM1602_write_cmd(0x0C); 
	LCM1602_write_cmd(0x80); 
   CLEARSCREEN; 
} 
 
////////////////////////////////////////////////////////////////////////////
//��LCD״̬
//////////////////////////////////////////////////////////////////////////// 
void LCM1602_Read_BF(void) 
{ 
	LCD1602_RW=1;		//RW 1 
	LCD1602_RS=0;		//RS 0 
	LCD1602_EN=1;		//EN 1	Read BF 
 	LCM1602_DATA=LCM1602_DATA&0x0F|0xf0; 
	while(LCM1602_DATA&0x80); 
	LCD1602_EN=0;		 
}

////////////////////////////////////////////////////////////////////////////
//LCDдʹ�ܣ�EN�˲���һ���ߵ�ƽ���壬дLCD 
////////////////////////////////////////////////////////////////////////////
void LCD_en_write(void)        //
  { 
    LCD1602_EN=1; 
	 LCD1602_EN=1;
    LCD1602_EN=0;	 
  } 
 
////////////////////////////////////////////////////////////////////////////
//дָ��
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_cmd(unsigned char command) 
{ 
	LCM1602_Read_BF(); 
	LCD1602_RS=0;   	//RS 0  
	LCD1602_RW=0;		//RW 0  
	 
	LCM1602_DATA&=0x0F; 
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
	command=command<<4;  
	LCM1602_DATA&=0x0F; 
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
} 

////////////////////////////////////////////////////////////////////////////
//д����
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_data(unsigned char dat) 
{ 
	LCM1602_Read_BF(); 
	LCD1602_RS=1;	 //RS 1  
	LCD1602_RW=0;	 //RW 0  
	LCM1602_DATA &=0x0F; 
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
	dat=dat<<4; 
	LCM1602_DATA &=0x0F; 
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
} 

////////////////////////////////////////////////////////////////////////////
//�趨��ʾλ��
////////////////////////////////////////////////////////////////////////////
void LCM1602_set_xy(unsigned char x,unsigned char y) 
{ 
	unsigned char address; 
	y&=0x0f; 
	if(!x)	 
		address=0x80+y; 
	else 			 
		address=0xc0+y; 
	LCM1602_write_cmd(address);  
} 

////////////////////////////////////////////////////////////////////////////
//��ָ��λ����ʾһ���ַ�
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat) 
{ 
	LCM1602_set_xy(x,y);  
	LCM1602_write_data(dat); 
} 

////////////////////////////////////////////////////////////////////////////
//��ָ��λ����ʾһ���ַ�
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_string(unsigned char x,unsigned char y,const unsigned char *s) 
{ 
	LCM1602_set_xy(x,y);  
	while(*s)   
	{ 
		LCM1602_write_data(*s);    
		s++; 
	} 
} 

////////////////////////////////////////////////////////////////////////////
//λ�����ݴ������ʵ����
//////////////////////////////////////////////////////////////////////////// 
void num(unsigned char x,unsigned char y,unsigned int n) 
{ 
	unsigned char i,length,a[6]={0,0,0,0,0,0}; 
	unsigned int nx=n; 
	if(n==0){LCM1602_write_char(x,y,'0');return;} 
	for(i=0;i<6;i++) 
	{ 
		if(nx>=1)length++; 
		nx/=10; 
	} 
	nx=n; 
	for(;length>0;length--) 
	{ 
		a[length-1]=nx%10+48; 
		nx/=10; 
	} 
	LCM1602_write_string(x,y,a); 
}

////////////////////////////////////////////////////////////////////////////
//��ʼֵdelayus(1)=27us,���9.9us 
////////////////////////////////////////////////////////////////////////////
void delay10us(unsigned int t) 
{ 
	while(t--); 
}

////////////////////////////////////////////////////////////////////////////
// 1ms��ʱ�ӳ���
////////////////////////////////////////////////////////////////////////////
void delayms(int ms)
{
 unsigned char y;
  while(ms--)
 {
  for(y = 0; y<250; y++)
  {
   _nop_();
   _nop_();
   _nop_();
   _nop_();
  }
 }
} 

////////////////////////////////////////////////////////////////////////////
//����ʼ���Ӻ���
////////////////////////////////////////////////////////////////////////////
void Init_mouse(void) 
{ 
     TCON=0x00; 
     EA=1; 
     EX1=1;   //�����ⲿ�ж�1 
     ET0=0x01;//����ȫ���жϣ�����ʱ��/������0����ж� 
     PX1=1;   //�����ж����ȼ� 
} 
 
////////////////////////////////////////////////////////////////////////////
//�������ݸ����
////////////////////////////////////////////////////////////////////////////
void mouse_send_data(unsigned char dat) 
{ 
	unsigned char i; 
	EX1=0;                    //�ر��ⲿ�ж�1
	ACC=dat;                  //��Ҫ���͵����ݷ���A�Ĵ���
	mouse_CLK=0;              //����ʱ����
	delay10us(200);           //��ʱ100us����
	mouse_SDA=0;              //����������
	delay10us(40); 
	mouse_CLK=1;              //�ͷ�ʱ����
	for(i=0;i<=7;i++)         //��λ��ǰ��һ�η���8������λ
	{ 
		while(mouse_CLK==1);   //�ȴ��豸����ʱ����
		mouse_SDA=(dat>>i)&0x01;//��������λ
		while(mouse_CLK==0);   //�ȴ��豸�ͷ�ʱ����
	} 
	while(mouse_CLK==1); 
	mouse_SDA=~P;             //����У��λ����У��
	while(mouse_CLK==0); 
	while(mouse_CLK==1); 
	mouse_SDA=1;              //����ֹͣλ
	while(mouse_CLK==0);							   
	while(mouse_CLK==1);		  //Ӧ��λ
	while(mouse_CLK==0);	 
	EX1=1;                    //���ⲿ�ж�1
} 
 
////////////////////////////////////////////////////////////////////////////
//��У���ӳ���
////////////////////////////////////////////////////////////////////////////
unsigned char Checkout(void)			 
{ 
	ACC=mouse_byte; 
	if(~P==mouse_buffer[9]) 
		return 1; 
	else 
		return 0; 
}  

////////////////////////////////////////////////////////////////////////////
//���ݷ����������ӳ���
////////////////////////////////////////////////////////////////////////////
void data_analyse(void) 
{ 
	//���յ���11λ�ź��н�ȡ8λ���ݷŽ�mouse_byte 
	mouse_byte_bit0=mouse_buffer[1]; 
	mouse_byte_bit1=mouse_buffer[2]; 
	mouse_byte_bit2=mouse_buffer[3]; 
	mouse_byte_bit3=mouse_buffer[4]; 
	mouse_byte_bit4=mouse_buffer[5]; 
	mouse_byte_bit5=mouse_buffer[6]; 
	mouse_byte_bit6=mouse_buffer[7]; 
	mouse_byte_bit7=mouse_buffer[8];	 
	if(Checkout())//���У����ȷ 
	{ 
		if(mouse_data_bit<3)          
			mouse_data[mouse_data_bit++]=mouse_byte;  
		if(mouse_data_bit==3) 
		{ 
			mouse_data_bit=0; 
			if(mouse_data[0]&0x10)//���"X sign bit"Ϊ1,��ʾ��������� 
			{ 
				move_x-=(256-mouse_data[1]);//x����� 
			} 
			else 
			{ 
				move_x+=mouse_data[1];//x�����
			} 
			if(mouse_data[0]&0x20) 
			{ 
				move_y-=(256-mouse_data[2]);//y�����
			} 
			else 
			{ 
				move_y+=mouse_data[2];//y����� 
			} 
		} 
	} 
} 

////////////////////////////////////////////////////////////////////////////
//�ⲿ�ж�1��������ʱ���ߴ���
////////////////////////////////////////////////////////////////////////////
void ReceiveData(void)  interrupt 2
{ 
	if(mouse_buffer_bit<=10) 
	{	                               	  
		while(mouse_CLK==0);//�ȴ��豸����ʱ���� 
		mouse_buffer[mouse_buffer_bit++]=mouse_SDA;//�������� 
	}	 
	if(mouse_buffer_bit==10) 
	{ 
		data_analyse();//���ݷ��������� 
		mouse_buffer_bit=0; 
	}			 	 					 
}

void main()   
{      
    Init_mouse();
    LCM1602_Init();
    mouse_send_data(0xf4);//����귢��0xF4�������俪ʼ����     
    EX1=0;//�ص��ⲿ�ж��Աܿ���귢�ص�Ӧ��
    delayms(100);
    EX1=1;//�ؿ��ⲿ�ж�
    while(1)   
    {          
        CLEARSCREEN;//����    
        LCM1602_write_string(0,0,"x:");   
        num(0,2,move_x);//x����ֵ    
        LCM1602_write_string(0,8,"y:");   
        num(0,10,move_y);//y����ֵ    
        if(mouse_data[0]&0x01)//����������    
        {
            beep=0;
            LCM1602_write_string(1,0,"Left Key is Down");   
        }   
        else if(mouse_data[0]&0x02)//��������Ҽ�    
        {   
            beep=0;
            LCM1602_write_string(1,0,"Right  Key  Down");   
        }   
        else if(mouse_data[0]&0x04)//��������м�    
        {   
            beep=0;
            LCM1602_write_string(1,0,"Middle Key Down!");   
        }   
        else   
        {   
            beep=1;
            LCM1602_write_string(1,0,"No Key  is Down!");   
        }
        delayms(50);   
    }   
}  