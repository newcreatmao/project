#ifndef __PID_H
#define __PID_H

#include<stm32f10x.h>
typedef struct 
{
	signed int  Sv;			//�û��趨ƽ��λ��ֵ
	float Pv;
					/*ƽ�⻷�����趨 */
	float  Kd;					//ƽ��΢����?��?
	signed int  Kp;			//ƽ�������ϵ��
	
	

	
					/*�ٶȻ������趨 */
	signed int left;      //Ŀ�����ٶ�
	signed int right;     //Ŀ�����ٶ�
	signed int move;     //Ŀ�����ٶ�
	float  Ki_speed;				//�ٶȻ�������ϵ��
	float Kp_speed;		//�ٶȻ�������ϵ��
	signed int EK_speed;  	//�ٶ�ƫ��
	signed int SEK_speed;   //��ʷƫ��֮��
	signed int DIF_speed;

					/*ת�򻷲����趨 */
	float Kp_turn;					//ת�򻷱�����ϵ��
	float Angle_turn;				//Ŀ��ת��Ƕ�
	
}PID;

int balance(float Angle);
void PID_Init(void);
int velocity(int encoder_left,int encoder_right);
//int velocity(int encoder_left,int encoder_right,int RPWM,float Angle);
//int turn(float gyro);
int turn(int encoder_left,int encoder_right,float gyro);


#endif