#include"Sys.h"
int16_t AX, AY, AZ, GX, GY, GZ;
int main()
{
	float Lspeed1=0,Lspeed2=0;
	float Rspeed1=0,Rspeed2=0;
	OLED_Init();
	
	MOTOR_GPIO_Config();
	TIM2_PWM_Init(999, 71 );
	MOTOR_GPIO_Config();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	MPU6050_Init();
	//电机TIM3编码器初始化
	encoder_Tim3_init();
	//电机TIM4编码器初始化
	encoder_Tim4_init();
	//MotorOutDirection(500,-500);
	
	PID_init();
	
	while(1)
	{	
        MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(3, 1, AX, 3);
		OLED_ShowSignedNum(3, 5, AY, 3);
		OLED_ShowSignedNum(3, 9, AZ, 3);
		OLED_ShowSignedNum(4, 1, GX, 3);
		OLED_ShowSignedNum(4, 5, GY, 3);
		OLED_ShowSignedNum(4, 9, GZ, 3);
		Lspeed1 = read_cnt_TIM3();
		OLED_ShowSignedNum(1,1,Lspeed1,6);
		Lspeed2=LPID_realize(20,Lspeed1);
		OLED_ShowSignedNum(1,8,Lspeed2,5);
		
		Rspeed1 = read_cnt_TIM4();
		OLED_ShowSignedNum(2,1,Rspeed1,6);
		Rspeed2=RPID_realize(20,Rspeed1);
		OLED_ShowSignedNum(2,8,Rspeed2,5);
		
		MotorOutDirection(200+Lspeed2,200+Rspeed2);
    }
}
		