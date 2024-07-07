#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "malloc.h"  
#include "MMC_SD.h"  
#include "string.h"
//��ȡSD����ָ�����������ݣ���ͨ������1���
//sec�����������ַ���
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
		LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
		LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
	}
	myfree(buf);//�ͷ��ڴ�	
}

 int main(void)
{ 
	u8 key;		 
	u32 sd_size;
	u8 t=0;	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD	
 	KEY_Init();				//������ʼ��  
 	mem_init();				//��ʼ���ڴ��	
	Use_lock_init();	 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,110,200,16,16,"2024/3/08");  
	LCD_ShowString(60,130,200,16,16,"KEY0:Read Sector 0");	   
 	while(SD_Initialize())//��ⲻ��SD��
	{
		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(60,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	//���SD���ɹ� 											    
	LCD_ShowString(60,150,200,16,16,"SD Card OK    ");
	LCD_ShowString(60,170,200,16,16,"SD Card Size:     MB");
	sd_size=SD_GetSectorCount();//�õ�������
	LCD_ShowNum(164,170,sd_size>>11,5,16);//��ʾSD������
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)SD_Read_Sectorx(0);//KEY0��,��ȡSD������0������
		t++;
		if(Serial_RxFlag==1){
			LCD_ShowString(60,210,200,16,16,Serial_RxPacket);
			if(strcmp(Serial_RxPacket,"Lock_open1 ")==0){
				Open_lock(1);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open2 ")==0){
				Open_lock(2);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open3 ")==0){
				Open_lock(3);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open4 ")==0){
				Open_lock(4);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open5 ")==0){
				Open_lock(5);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close1")==0){
				Lock(1);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close2")==0){
				Lock(2);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close3")==0){
				Lock(3);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close4")==0){
				Lock(4);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close5")==0){
				Lock(5);
			}
			else{
				SD_WriteDisk(Serial_RxPacket,0,1);
			}
			
			Serial_RxFlag=0;
		}
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;
			t=0;
		}
	}    	   
}



