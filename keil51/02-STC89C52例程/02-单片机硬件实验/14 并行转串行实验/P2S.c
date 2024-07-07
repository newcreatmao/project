/***************************************************************************
ÊµÑéÃû³Æ£º ²¢ÐÐ×ª´®ÐÐÊµÑé

ÊµÑéÄ£¿é:  51µ¥Æ¬»úºËÐÄ°å¡¢²¢ÐÐ×ª´®ÐÐÇø¡¢²¦Âë¿ª¹ØÇø¡¢LEDÏÔÊ¾Çø

ÊµÑé½ÓÏß£º  51µ¥Æ¬»úºËÐÄ°å------²¢ÐÐ×ª´®ÐÐÇø
					P1.0---------SLK
					P1.1---------SDA
					P1.2---------SFT_LD
					
			51µ¥Æ¬»úºËÐÄ°å------LEDÏÔÊ¾Çø
					P0  ---------J4
					
			²¢ÐÐ×ª´®ÐÐÇø------²¦Âë¿ª¹ØÇø
					J8	--------- J1
						
ÏÖÏóÃèÊö£º	²¦¶¯¿ª¹ØSW1~SW8¿ØÖÆLEDµÆD1~D8µÄÁÁÃð

¸üÐÂÊ±¼ä£	º2017.10.17
***************************************************************************/

#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
                                                   
sbit CLK = P1^0;
sbit SDA = P1^1;
sbit SF  = P1^2;


void mDelay(uint Delay)	//ÑÓÊ±
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

uchar receive() 	   //ÊÕÈ¡×Ö½ÚµÄ³ÌÐò
{     
	uchar byte = 0,c;  
	for(c = 0; c < 8; c++) 		
	{ 
		byte = byte<<1; 		//Êý¾Ý×óÒÆÒ»Î»
		CLK = 1;
		CLK = 0;
		if(SDA) 				//ÊÕÈ¡×îµÍÎ»Êý¾Ý
			byte = byte|0x01; 		
		CLK = 1;

	       
	} 
	return(byte);
} 


void main() //Ö÷³ÌÐò
{
	uchar a = 0;
	while(1)
	{
		SF = 1;			   		//ËøÈëÊý¾Ý
		SF = 0;
		SF = 1;
		a = receive();
		P0 = a;
 
	}
}

