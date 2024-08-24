#include "sys.h"

float pitch,roll,yaw;

int main(void)
{
	OLED_Init();
	mpu_dmp_init();
	while (1)
	{
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		
		OLED_ShowSignedNum(1, 1,pitch, 2);
		OLED_ShowSignedNum(2, 1,roll, 2);
		OLED_ShowSignedNum(3, 1,yaw, 2);
	}
}
