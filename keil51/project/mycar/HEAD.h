#ifndef __HEAD_H__
#define __HEAD_H__
#include <REGX52.H>
/**
  * @brief  ���
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
  * @brief  ѭ��
  */
	sbit clx = P3^3;
	sbit crx = P3^7;
	sbit mlx = P3^2;
	sbit mrx = P3^6;
	
/**
	* @brief ������
	*/
	sbit TRIG = P2^1;//���峬������෢�Ͷ�
  sbit ECHO = P2^0;//���峬���������ն�
	
/**
  * @brief  ���ϵ�
  */
	sbit left = P3^4;
	sbit right = P3^5;
	
/**
  * @brief  ��������
  */
	sbit key1 = P1^7;
	sbit key2 = P1^6;
	sbit key3 = P1^5;
	sbit key4 = P1^4;

/**
  * @brief  ������
  */
	sbit bee = P2^3;//��������2.3

/**
  * @brief  ���״̬
  */
	sbit efl=P0^2;
	sbit efg=P0^3;
	sbit ebl=P0^0;
	sbit ebg=P0^1;

#endif