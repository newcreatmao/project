#include <REGX52.H>
sbit IN3 = P1^6;
sbit IN4 = P1^7;//ÓÒÂÖ
sbit IN1 = P1^3;
sbit IN2 = P1^2;//×óÂÖ

void car_lf_go()
{IN1=1;IN2=0;}

void car_rg_go()
{IN3=1;IN4=0;}

void car_lf_back()
{IN1=0;IN2=1;}

void car_rg_back()
{IN3=0;IN4=1;}

void turn_left_go()
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=0;
}

void turn_left_back()
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=0;
}

void turn_right_go()
{
	IN1=0;
	IN2=0;
	IN3=1;
	IN4=0;
}

void turn_right_back()
{
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=1;
}

void car_lf_stop()
{IN1=0;IN2=0;}

void car_rg_stop()
{IN3=0;IN4=0;}