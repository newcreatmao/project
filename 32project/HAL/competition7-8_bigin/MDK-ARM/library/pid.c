#include "pid.h"

PID pwm;

void init_pwm(int p,int i,int d)
{
	pwm.Kp = p;
	pwm.Ki = i;
	pwm.Kd = d;
	
}

float pwm_pid(float target,float current,float last)
{
	float out;
	pwm.err = target - current;
	pwm.err_last=last;
	out = pwm.Ki*pwm.err + pwm.Kp*(pwm.err-pwm.err_last);
	return out;
}

