#include"PID.h"

struct _pid{
	float SetSpeed; //�����趨ֵ
	float ActualSpeed; //����ʵ��ֵ
	float err; //����ƫ��ֵ
	float err_last; //������һ��ƫ��ֵ
	float Kp,Ki,Kd; //������������֡�΢��ϵ��
	float voltage; //�����ѹֵ������ִ�����ı�����
	float integral; //�������ֵ
}Lpid,Rpid;

void PID_init(void){
	Lpid.SetSpeed=0.0;
	Lpid.ActualSpeed=0.0;
	Lpid.err=0.0;
	Lpid.err_last=0.0;
	Lpid.voltage=0.0;
	Lpid.integral=0.0;
	Lpid.Kp=1.1;
	Lpid.Ki=0.000;
	Lpid.Kd=0.00;
	Rpid.SetSpeed=0.0;
	Rpid.ActualSpeed=0.0;
	Rpid.err=0.0;
	Rpid.err_last=0.0;
	Rpid.voltage=0.0;
	Rpid.integral=0.0;
	Rpid.Kp=1.0;
	Rpid.Ki=0.000;
	Rpid.Kd=0.00;
}

float LPID_realize(float speed,float Actual){
	float index;
	Lpid.SetSpeed=speed;
	Lpid.ActualSpeed=Actual;
	Lpid.err=Lpid.SetSpeed-Lpid.ActualSpeed;
	if(fabsf(Lpid.err)>200) //����ֹ���
	{
	index=0.0;
	}else if(fabsf(Lpid.err)<180){
	index=1.0;
	Lpid.integral+=Lpid.err;
	}else{
	index=(200-fabsf(Lpid.err))/20;
	Lpid.integral+=Lpid.err;
	}
	Lpid.voltage=Lpid.Kp*Lpid.err+index*Lpid.Ki*Lpid.integral+Lpid.Kd*(Lpid.err-Lpid.err_last);
	Lpid.err_last=Lpid.err;
	Lpid.ActualSpeed=Lpid.voltage*25.0;
	return Lpid.ActualSpeed;
}
float RPID_realize(float speed,float Actual){
	float index;
	Rpid.SetSpeed=speed;
	Rpid.ActualSpeed=Actual;
	Rpid.err=Rpid.SetSpeed-Rpid.ActualSpeed;
	if(fabsf(Rpid.err)>200) //����ֹ���
	{
	index=0.0;
	}else if(fabsf(Rpid.err)<180){
	index=1.0;
	Rpid.integral+=Rpid.err;
	}else{
	index=(200-fabsf(Rpid.err))/20;
	Rpid.integral+=Rpid.err;
	}
	Rpid.voltage=Rpid.Kp*Rpid.err+index*Rpid.Ki*Rpid.integral+Rpid.Kd*(Rpid.err-Rpid.err_last);
	Rpid.err_last=Rpid.err;
	Rpid.ActualSpeed=Rpid.voltage*25.0;
	return Rpid.ActualSpeed;
}



