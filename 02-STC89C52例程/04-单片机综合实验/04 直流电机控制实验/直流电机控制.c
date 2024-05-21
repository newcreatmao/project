/***************************************************************************
ÊµÑéÃû³Æ£º  Ö±Á÷µç»ú²âËÙÊµÑé³ÌÐò 

ÊµÑéÄ£¿é£	51µ¥Æ¬»úºËÐÄ°å¡¢Ö±Á÷µç»úÇø¡¢LCD12864ÏÔÊ¾Çø ¡¢¼òÒ×À©Õ¹IOÇø¡¢¾ØÕó¼üÅÌÇø

ÊµÑé½ÓÏß£º	 51µ¥Æ¬»úºËÐÄ°å------LCD12864ÏÔÊ¾Çø
				   P2.0--------------CS1
				   P2.1--------------CS2
				   P2.2--------------CS
				   P2.3--------------RW
				   P2.4--------------E
			  P0.0~P0.7--------------DB0~DB7
				
			 51µ¥Æ¬»úºËÐÄ°å------¼òÒ×À©Õ¹IOÇø		
				  P3.0--------------A0				   						 
				  P3.1--------------A1
					   
					T/R½Ó+5V  nOE ½ÓGND
			 51µ¥Æ¬»úºËÐÄ°å------Ö±Á÷µç»úÇø	   
				 P3.2--------------SPEED
			 ¼òÒ×À©Õ¹IOÇø ------  Ö±Á÷µç»úÇø 
				  B0--------------MOTO1
				  B1 --------------MOTO2
			51µ¥Æ¬»úºËÐÄ°å------¾ØÕó¼üÅÌÇø
				  P1 -------------- MK1
				  
ÏÖÏóÃèÊö£L°´¶¯¾ØÕó¼üÅÌÏàÓ¦°´¼ü£¬Ö±Á÷µç»úÖ´ÐÐÏà¹Ø¹¦ÄÜ¡£
		  

¸üÐÂÊ±¼ä£º2017.08.18
***************************************************************************/ 


#include <reg52.h> 
#include<12864.c>    
#define uchar unsigned char
#define uint unsigned int

#define CIRCLE 25  //ËÙ¶È¿Éµ÷½ÚµÄµµÎ»ÉèÖÃ

uchar count=1,last=10;
uchar temp,key;
uint time,speed;
bit  PWM,flag=0;
uchar kt=0;
sbit Moto1 = P3^0;
sbit Moto2 = P3^1;

void mDelay(uint Delay)	//ÑÓÊ±
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 110;i++);
}
void Timer0(void) interrupt 1  //¶¨Ê±Æ÷0Òç³öÖÐ¶Ï·þÎñ×Ó³ÌÐò£¬ÓÃÓÚ²úÉúPWM²¨
{
   count++;
   if(count>CIRCLE) 
     {
        count=1;
     } 
   if(count<=last)
      PWM=0;
   else 
      PWM=1;
   TH0=0xFC;
   TL0=0x66;
}

void INT_0 (void) interrupt 0  //Íâ²¿ÖÐ¶Ï0ÖÐ¶Ï·þÎñ×Ó³ÌÐò£¬ÓÃÓÚ¼ÇÂ¼²âËÙÆ÷Ä£¿é²úÉúµÄÂö³åÊýÄ¿
{
   EX0=0;    //½ûÖ¹Íâ²¿ÖÐ¶Ï0ÖÐ¶Ï
   time++;
   EX0=1;    //ÔÊÐíÍâ²¿ÖÐ¶Ï0ÖÐ¶Ï
}



void Timer1 (void) interrupt 3 //¶¨Ê±Æ÷1Òç³öÖÐ¶Ï·þÎñ×Ó³ÌÐò£¬ÓÃÓÚ»ñÈ¡ËÙ¶ÈÖµ
{
   TH1=0x4C;      //ÖØ×°¶¨Ê±³õÖµ
   TL1=0x00;      //50ms¶¨Ê±
   time=time*300;        //·ÀÖ¹¸öÎ»±»È¥³ý
   speed=(time/3)*20;    //ËÙ¶È£ºr/s
   speed=speed/300;
   time=0;
}


void INT_Init() //ÏµÍ³³õÊ¼»¯º¯Êý£¬³õÊ¼»¯¶¨Ê±Æ÷T0¡¢T1ºÍÍâ²¿ÖÐ¶Ï0
{
   TMOD=0x10;     //Ñ¡ÔñT1¹¤×÷ÓÚ·½Ê½1
   TH1=0x4C;
   TL1=0x00;      //50ms¶¨Ê±
   ET1=1;         //ÔÊÐíT1ÖÐ¶Ï
   TR1=1;         //Æô¶¯T1ÖÐ¶Ï

   ET0=1;         //ÔÊÐíT0ÖÐ¶Ï
   TH0=0xFC;
   TL0=0x66;
   TR0=1;         //Æô¶¯T0ÖÐ¶Ï

   IT0=1;         //ÏÂ½µÑØ´¥·¢
   EX0=1;         //ÔÊÐíÍâ²¿ÖÐ¶Ï0ÖÐ¶Ï

   EA=1;          //¿ªËùÓÐÖÐ¶Ï

   	LCD12864_Init();
	LCD12864_Clear();
	Display();
}

/**********************************************************/
// ¼üÉ¨Ãè×Ó³ÌÐò
void  keyscan(void)
 { 
    P1=0xF0;                //ÐÐÏßÎªÊäÈë£¬ÁÐÏßÎªÊä³ö£¬²¢ÖÃÁÐÏßÊä³öÈ«Îª0
	temp=P1;                //¶ÁP1¿Ú       
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
    P1=0x0F;                 //ÁÐÏßÎªÊäÈë£¬ÐÐÏßÎªÊä³ö£¬²¢ÖÃÐÐÏßÊä³öÈ«Îª0  
	 temp=P1;                 //¶ÁP1¿Ú 
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
//ÅÐ¶Ï¼üÊÇ·ñ°´ÏÂ
void  keydown(void)
 {  

  	P1=0xF0;
    mDelay(5);
	if(P1!=0xF0)
	{
	  keyscan();
	  	switch(mm[key])
		{
			case 0:
				kt=1;
				break;	
			case 2:
				last--;
				if(last<1)
					last=25;
				break;	
			case 4:
				flag=0;
				break;	
			case 5:
				kt=0;
				break;	
			case 6:
				flag=1;
				break;	
			case 8:
				last++;
				if(last>=25)
					last=1;
				break;	
			default:	
				break;
			
		}
    }
 }
void main(void)   //Ö÷º¯Êý
{

	INT_Init();
	while(1)
	{
		keydown();
		display(key,speed);
		if(kt)
		{		
			if(flag)//Õý´«
			{
				Moto1=PWM;
				Moto2=0;
			}
			if(!flag)//·´´«
			{
				Moto2=PWM;
				Moto1=0;
			}
		}
		else 
		{
			Moto2=0;
			Moto1=0;			
		}
	}
}