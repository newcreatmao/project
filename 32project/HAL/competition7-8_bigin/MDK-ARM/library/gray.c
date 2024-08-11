#include "gray.h"
#include "oled.h"
#include "drive.h"
uint8_t L1,L2,L3,M,R1,R2,R3;
uint32_t result;
int16_t l_speed,r_speed,base_speed=0,out;

void Speed_Init(uint8_t l_speed,uint8_t r_speed)
{
L_speed(l_speed);
R_speed(r_speed);
}

/*		判断地面黑线
			检测到黑线 		1
			未检测到黑线 	0
			返回一个数  0001000 表示中间检测到黑线
*/
uint8_t SCAN_ground(void)
{

	
	int16_t pid_ground;
	
	if(	HAL_GPIO_ReadPin(L1_PORT,L1_PIN)==RESET)//L1
		L1=0;
	else L1=1;

	if(	HAL_GPIO_ReadPin(L2_PORT,L2_PIN)==RESET)//L2
		L2=0;
	else L2=1;
	
	if(	HAL_GPIO_ReadPin(L3_PORT,L3_PIN)==RESET)//L3
		L3=0;
	else L3=1;
	
	if(	HAL_GPIO_ReadPin(M_PORT,M_PIN)==RESET)//M
		M=0;
	else M=1;
	
	if(	HAL_GPIO_ReadPin(R3_PORT,R3_PIN)==RESET)//R3
		R3=0;
	else R3=1;
	
	if(	HAL_GPIO_ReadPin(R2_PORT,R2_PIN)==RESET)//R2
		R2=0;
	else R2=1;
	
	if(	HAL_GPIO_ReadPin(R1_PORT,R1_PIN)==RESET)//R1
		R1=0;
	else R1=1;
	
	result=L1*1000000+L2*100000+L3*10000+M*1000+R3*100+R2*10+R1*1;//返回一个数
	
// switch(result)
//	{ 
//	
//		
//	  case 0000001:			L_speed(0);R_speed(90);break;				
//		case 0000010:			L_speed(15);R_speed(75);break;		
//		case 0000100:			L_speed(30);R_speed(60);break;				//left
//		
//		case 0001000:		  L_speed(50);R_speed(50);break;				//middle
//		
//		case 0010000:			L_speed(60);R_speed(30);break;						//right
//		case 0100000:			L_speed(75);R_speed(15);break;		
//		case 1000000:			L_speed(90);R_speed(0);break;		
//		
//		
//		case 0000000:     pwm.err_last=pwm.err;break;
//		default:pwm.err=100;
//	}
	
	
  switch(result)
	{
	  case 			 1:			pwm.err=-30;break;				
		case      10:			pwm.err=-20;break;	
		case     100:			pwm.err=-10;break;					//left
		
		case    1000:		  pwm.err=0;break;				  //middle
		
		case   10000:			pwm.err=10;break;					//right
		case  100000:			pwm.err=20;break;	
		case 1000000:			pwm.err=30;break;	
		
		
		case 0000000:     pwm.err_last=pwm.err;break;
		
		case 1111111:     {L_speed(0);R_speed(0);}break;
		default:pwm.err_last=pwm.err;
	}
	  out=pwm_pid(0,pwm.err,pwm.err_last);
	  l_speed=base_speed+out;
		r_speed=base_speed-out;
		
	 if(l_speed>1000)l_speed=1000;
	 if(l_speed<-1000)l_speed=-1000;
	 if(r_speed>1000)r_speed=1000;
	 if(r_speed<-1000)r_speed=-1000;
	
	  L_speed(l_speed);
	  R_speed(r_speed);
	
		return pid_ground;

}

 

//uint8_t xunji(void)
//{ Speed_Init(0,0);
//	pwm_pid(0001000,SCAN_ground());
//	init_pwm(1,1,1);
//	
//	


//}



//uint8_t PID_retrun(void)
//{	uint32_t ground;
//	int16_t pid_ground;
//	ground=SCAN_ground();
//  switch(ground)
//	{
//	  case 0000001:			pid_ground=-3;				
//		case 0000010:			pid_ground=-2;
//		case 0000100:			pid_ground=-1;			//left
//		
//		case 0001000:		  pid_ground=0;				//middle
//		
//		case 0010000:			pid_ground=1;				//right
//		case 0100000:			pid_ground=2;
//		case 1000000:			pid_ground=3;
//		
//	
//	}

//	return pid_ground;
//}
//	


	
