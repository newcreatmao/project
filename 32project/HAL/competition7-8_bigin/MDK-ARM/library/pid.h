#ifndef _PID__H_
#define	_PID__H_
					typedef struct {
					float SetSpeed; //�����趨ֵ
					float ActualSpeed; //����ʵ��ֵ
					float err; //����ƫ��ֵ
					float err_last; //������һ��ƫ��ֵ
					float Kp,Ki,Kd; //������������֡�΢��ϵ��
					float voltage; //�����ѹֵ������ִ�����ı�����
					float integral; //�������ֵ
					}PID;
					
					extern PID pwm;
					
					void init_pwm(int p,int i,int d);
					float pwm_pid(float target,float current,float last);
					void hello(void);
#endif	
