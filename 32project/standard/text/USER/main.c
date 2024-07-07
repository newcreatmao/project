#include "use.h"

int main(void)
{ 
	u8 key,Flag=0;		 
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
		if(key==KEY1_PRES)SD_Read_Sectorx(1);//KEY1��,��ȡSD������1������
		else if(key==KEY0_PRES) Flag=(Flag+1)%2;
		
		if(Flag==0){Lock_show();}
		else {SD_rw();}
		t++;
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;
			t=0;
		}
	}    	   
}
