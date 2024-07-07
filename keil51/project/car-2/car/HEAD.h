#ifndef __HEAD_H__
#define __HEAD_H__
#include <REG52.H>
/**
  * @brief  电机
  */
  
sbit IN1=P1^2;
sbit IN2=P1^3;
sbit IN3=P1^6;
sbit IN4=P1^7;
sbit EN1=P1^4;
sbit EN2=P1^5;

/**
  * @brief  数码管
  */
	sbit WS=P2^7;
	sbit MS=P2^6;
	
/**
  * @brief  循迹
  */
sbit left_led=P3^3;
sbit right_led=P3^2;
/**
	* @brief 超声波
	*/
sbit TRIG = P2^1;//定义超声波测距发送端
sbit ECHO = P2^0;//定义超声波测距接收端

/**
  * @brief  独立按键
  */
sbit key2=P3^0;
sbit key3=P3^1;
sbit key4=P3^2;
sbit key5=P3^3;


/**
  * @brief  蜂鸣器
  */

sbit beep = P2^3;


/**
  * @brief  电机状态
  */

#define left_motor_en		EN1=1
#define left_motor_go		IN1=0,IN2=1
#define left_motor_back		IN1=1,IN2=0
#define left_motor_stop		IN1=0,IN2=0

#define right_motor_en		EN2=1
#define right_motor_go		IN3=1,IN4 =0
#define right_motor_back	IN3=0,IN4 =1
#define right_motor_stop	IN3=0,IN4 =0	


#endif