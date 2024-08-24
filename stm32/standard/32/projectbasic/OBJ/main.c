#include "stm32f10x.h"// Device header
#include"motor.h"
#include"OLED.h"
#include"Key.h"
#include"Search.h"
#include"MPU6050.h"
int16_t AX, AY, AZ, GX, GY, GZ;
int main(){
    int j=50,i=0;
    OLED_Init();
    ENA_PWMInit();
    Motor_Init();
    KEY_INITA();
    KEY_INITB();
	BianA_init();
    BianB_init();
    MPU6050_Init();
    OLED_ShowString(1,1,"Funtion:");
    OLED_ShowString(2,1,"A:");
    OLED_ShowString(2,7,"B:");
    OLED_ShowString(2,12,"cm/s");
    while(1){
        MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
        int keynum=KEY_GETNUM();
        if(keynum==1){
            i=0;
            moto(i,j);            
        }
        else if(keynum==2){
            i=1;
            moto(i,j);
        }
        else if(keynum==3){
            j+=5;
            j%=100;
            moto(i,j);
        }
        else if(keynum==4){
            j-=5;
            j%=100;
            moto(i,j);
        }
        OLED_ShowNum(2,3,ENcoderA(),3);
        OLED_ShowNum(2,9,ENcoderB(),3);
        OLED_ShowNum(1,10,i,1);
        OLED_ShowSignedNum(3, 1, AX, 4);
		OLED_ShowSignedNum(3, 6, AY, 4);
		OLED_ShowSignedNum(3, 11, AZ, 4);
		OLED_ShowSignedNum(4, 1, GX, 4);
		OLED_ShowSignedNum(4, 6, GY, 4);
		OLED_ShowSignedNum(4, 11, GZ, 4);
    }
}