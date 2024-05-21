/***************************************************************************
ʵ�����ƣ� ����ʱ��ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢Һ����ʾ����12864����ʱ�����������������������������

ʵ����ߣ�	51��Ƭ�����İ�------ʱ��������
					 P2.6--------------SDA
					 P2.7--------------SCL
					 
		    51��Ƭ�����İ�------���������		 
					 P1  --------------MK1
					 
			51��Ƭ�����İ�------��������
					 P3.0--------------PUL
					 
			51��Ƭ�����İ�------Һ����ʾ����12864�ַ�Һ����
					 P2.0--------------CS1
					 P2.1--------------CS2
					 P2.2--------------CS
					 P2.3--------------RW
					 P2.4--------------E
				P0.0~P0.7--------------DB0~DB7		
						
����������	12864��ʾʱ�䡢����

����ʱ�䣺	2017.10.22
***************************************************************************/

#include <reg52.h>	//��ӿ��ļ�
#include <12864.c>
#include <I2C.h>
#include <PCF8563.h>
			//����IO�Ͳ����Ķ�������ͷ�ļ���
uchar temp,key,flag;
uchar num0=1;
uchar num1;
void ss(uchar a,uchar b,uchar x,uchar y)
{

	LCD_CS1=a;
	LCD_CS2=b;
	LCD12864_Disp(x,y,Dot[12]);
	mDelay(500);



}

/**********************************************************/// ��ɨ���ӳ���
void  keyscan(void)
 { 
    P1=0xF0;                //����Ϊ���룬����Ϊ����������������ȫΪ0
	temp=P1;                //��P1��       
    temp=temp&0xF0;
    temp=~((temp>>4)|0xF0);
    if(temp==1)
        key=0;
    else if(temp==2)
        key=1;
    else if(temp==4)
        key=2;
    else if(temp==8)
        key=3;
    P1=0x0F;                 //����Ϊ���룬����Ϊ����������������ȫΪ0  
	 temp=P1;                 //��P1�� 
    temp=temp&0x0F;
    temp=~(temp|0xF0);        
    if(temp==1)
        key=key+0;
    else if(temp==2)
        key=key+4;
    else if(temp==4)
        key=key+8;
    else if(temp==8)
        key=key+12;

	while(temp)
	{
		P1=0x0F;                 
		temp=P1;                
		temp=temp&0x0F;
		temp=~(temp|0xF0); 
	}

 }

/*************************************************************/
//�жϼ��Ƿ���
void  keydown(void)
 {  

  	P1=0xF0;
    mDelay(5);
	if(P1!=0xF0)
	{
	  	keyscan();
	   	if(mm[key]==10)
		{		
			LCD12864_Clear();
			LCD_CS1=0;
			LCD_CS2=1;
			LCD12864_Disp(0,24,Dot[6]);                
			LCD12864_Disp(0,40,Dot[7]);
			LCD12864_DispNum(3,16,num[2]);
			LCD12864_DispNum(3,24,num[0]);
			LCD12864_Disp(3,48,Dot[0]);                                              
			LCD_CS1=1;
			LCD_CS2=0;	                
			LCD12864_Disp(0,0,Dot[0]);                  
			LCD12864_Disp(0,16,Dot[1]);
			LCD12864_Disp(0,32,Dot[2]);
			LCD12864_Disp(3,16,Dot[1]);
			LCD12864_Disp(3,48,Dot[2]);
			flag=1;
			num0=1;
			
		}
		if(mm[key]==11)
		{		
			LCD12864_Clear();
			LCD_CS1=0;
			LCD_CS2=1;
			LCD12864_Disp(0,24,Dot[6]);                
			LCD12864_Disp(0,40,Dot[7]);                              
			LCD12864_DispNum(6,56,num[16]);                 
			LCD_CS1=1;
			LCD_CS2=0;	                
			LCD12864_Disp(0,0,Dot[4]);                  
			LCD12864_Disp(0,16,Dot[8]);
			LCD12864_Disp(0,32,Dot[9]);
			LCD12864_DispNum(6,16,num[16]);
			flag=2;
			num0=1;
		}
		if(mm[key]==12)
		{		
			LCD12864_Clear();
			LCD_CS1=0;
			LCD_CS2=1;
			LCD12864_Disp(0,24,Dot[6]);                
			LCD12864_Disp(0,40,Dot[7]);                              
			LCD12864_DispNum(6,56,num[16]);                 
			LCD_CS1=1;
			LCD_CS2=0;	                
			LCD12864_Disp(0,0,Dot[10]);                  
			LCD12864_Disp(0,16,Dot[11]);
			LCD12864_DispNum(6,16,num[16]);
			flag=3;
			num0=1;
		}
		if(mm[key]==13)
		{		
			LCD12864_Clear();
			Display();
			flag=0;
			xx=0;
		}
		if(mm[key]==14)
		{
			num0--;
			if(num0<1)
			num0=3;
	
		}	
		if(mm[key]==15)
		{
			num0++;
			if(num0>3)
			num0=1;
		}
		  if(flag==1)
		  {
			if(num0==1)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x08,num1);
				}
			}
			if(num0==2)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x07,num1);
				}
			}
			if(num0==3)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x05,num1);
				}
			}
		
		  }
		
		  if(flag==2)
		  {
			if(num0==1)
			{
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x04,num1);
				}
			}
			if(num0==2)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x03,num1);
				}
			}
			if(num0==3)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					SetPCF8563(0x02,num1);
				}
			}
		
		  }

		  if(flag==3)
		  {
			if(num0==1)
			{
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					tt[2]=num1;

				}
			}
			if(num0==2)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					tt[1]=num1;
				}
			}
			if(num0==3)
			{	
				if(mm[key]<10)
				{
					num1=num1<<4;
					num1|=mm[key];
					tt[0]=num1;
				}
			}
		
		  }



    }
 }
void keyjc(void)
{
  if(flag==1)
  {
	if(num0==1)
	{
		ss(0,1,3,32);	
	}
	if(num0==2)
	{
		ss(1,0,3,0);	
	}
	if(num0==3)
	{
		ss(1,0,3,32);	
	}

  }

  if(flag==2)
  {
	if(num0==1)
	{
		ss(0,1,6,40);	
	}
	if(num0==2)
	{
		ss(1,0,6,0);	
	}
	if(num0==3)
	{
		ss(1,0,3,24);	
	}

  }
  if(flag==3)
  {
	if(num0==1)
	{
		ss(0,1,6,40);	
	}
	if(num0==2)
	{
		ss(1,0,6,0);	
	}
	if(num0==3)
	{
		ss(1,0,3,24);	
	}

  }
}
void init()
{
	 LCD12864_Init(); 	//LCD��ʼ��
	 LCD12864_Clear();
	 Display();

/*     SetPCF8563(0x02,0x00);
     SetPCF8563(0x03,0x00);
     SetPCF8563(0x04,0x00);
     SetPCF8563(0x05,0x01);
     SetPCF8563(0x07,0x01);
     SetPCF8563(0x08,0x00);
  */
}

void main(void)
{    
	init();																														 
    while(1)
	{  
        time_display(flag);
		keydown();
		keyjc();
    }						 
}


