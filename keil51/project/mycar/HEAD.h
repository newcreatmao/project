#ifndef __HEAD_H__
#define __HEAD_H__
#include <REGX52.H>
/**
  * @brief  电机
  */
  sbit blf=P1^0;
	sbit blb=P1^1;
	sbit bgf=P1^3;
	sbit bgb=P1^2;
	sbit flb=P0^4;
	sbit flf=P0^5;
	sbit fgb=P0^7;
	sbit fgf=P0^6;
		
/**
  * @brief  循迹
  */
	sbit clx = P3^3;
	sbit crx = P3^7;
	sbit mlx = P3^2;
	sbit mrx = P3^6;
	
/**
	* @brief 超声波
	*/
	sbit TRIG = P2^1;//定义超声波测距发送端
  sbit ECHO = P2^0;//定义超声波测距接收端
	
/**
  * @brief  避障灯
  */
	sbit left = P3^4;
	sbit right = P3^5;
	
/**
  * @brief  独立按键
  */
	sbit key1 = P1^7;
	sbit key2 = P1^6;
	sbit key3 = P1^5;
	sbit key4 = P1^4;

/**
  * @brief  蜂鸣器
  */
	sbit bee = P2^3;//板子上是2.3

/**
  * @brief  电机状态
  */
	sbit efl=P0^2;
	sbit efg=P0^3;
	sbit ebl=P0^0;
	sbit ebg=P0^1;

#endif