// #include "stm32f10x.h"

// // PID����
// float Kp = 0.5;
// float Ki = 0.2;
// float Kd = 0.1;

// // Ŀ��λ��
// float targetPosition = 0;

// // ��ǰλ��
// float currentPosition = 0;

// // PID����������
// float lastError = 0;
// float integral = 0;

// // PID���ƺ���
// void PID_Control()
// {
//     // ���㵱ǰ���
//     float error = targetPosition - currentPosition;

//     // ���������
//     float control = Kp * error + Ki * integral + Kd * (error - lastError);

//     // ����PID����������
//     lastError = error;
//     integral += error;

//     // ִ�п��ƶ���
//     // TODO: ��������ӿ��ƶ����Ĵ���
// }

// int main()
// {
//     // ��ʼ��Ӳ���Ͳ�������
//     // TODO: ��������ӳ�ʼ������

//     while (1)
//     {
//         // ��ȡ��ǰλ��
//         // TODO: ��������Ӷ�ȡ��ǰλ�õĴ���

//         // ִ��PID����
//         PID_Control();

//         // ���¿�������
//         // TODO: ��������Ӹ��¿������ڵĴ���
//     }

//     return 0;
// }

// typedef struct {
//     float Kp;     //����ϵ��
//     float Ki;     //����ϵ��
//     float Kd;     //΢��ϵ��
//     float target_val;     //Ŀ��ֵ
//     float actual_val;     //ʵ��ֵ
//     float err;     //���
//     float integral;     //����ۻ�
//     float err_last;     //�ϴ����
// } PID;

// float PID_realize(float temp_val) {
//     static PID pid;     //��̬�����������ϴε�״̬
    
//     pid.target_val = temp_val;
//     pid.err = pid.target_val - pid.actual_val;
//     float increment_val = pid.Kp * (pid.err - pid.err_last) + pid.Ki * pid.err + pid.Kd * (pid.err - 2 * pid.err_last + pid.err_next);
//     pid.actual_val += increment_val;
//     pid.err_last = pid.err_next;
//     pid.err_next = pid.err;
    
//     return pid.actual_val;
// }



#include"Pid.h"
PID pid;

/**************************************************************************
�������ܣ�PID���ݳ�ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void PID_Init()
{
    /*ƽ��PID�����Ʋ�����ʼ��*/
    //P��Ӧ��Ӧ����
    pid.Sv =  0;
    pid.Kp =-97; //0_720,����Ϊ168
    pid.Kd = -138;//190

////////								/*�ٶ�PID�����Ʋ�����ʼ��*/
    pid.Kp_speed =-1800;
    pid.Ki_speed = pid.Kp_speed/200;//-0.066
    pid.EK_speed = 0;
    pid.SEK_speed = 0;

    pid.left = 0;
    pid.right = 0;				//�ٶȳ�ʼֵ
    //65 2
    /*ת��PID�����Ʋ�����ʼ��*/
    pid.Kp_turn =0;
    pid.Angle_turn = 0;
    /*�ٶ�PID�����Ʋ�����ʼ��*/

}


/**************************************************************************
�������ܣ����������������ֱ�����������PIDֵ��������
��ڲ�����δ֪
����  ֵ����
**************************************************************************/


/*С��ƽ�⻷���֣�΢��+��������
΢�ֱ���Ϊֱ�Ӷ�ȡ�ļ��ٶ�*/
extern short gyroy;
int balance(float Angle)
{

    signed  int  Bias;
    int balance;
    Bias=(Angle-pid.Sv)+pid.move;
    balance=pid.Kp*Bias+gyroy*pid.Kd/100;

    return balance;
}
/*
�������ܣ��ٶ�PI����
��ڲ�����encoder_left�������ٶ�
					encoder_right�������ٶ�
����  ֵ���ٶȿ���PWM
��    �ߣ�ǿ���CSDN�û�
*/
int velocity(int encoder_left,int encoder_right)
{
    static float Velocity,Encoder_Least,Encoder,Movement;
    static float Encoder_Integral;
//	  float kp=-90,ki=-0.45;
    //=============�ٶ�PI������=======================//
    Encoder_Least =(encoder_left+encoder_right)-0;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩
    Encoder *= 0.7;		                                                //===һ�׵�ͨ�˲���
    Encoder += Encoder_Least*0.3;	                                    //===һ�׵�ͨ�˲���
    Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
    Encoder_Integral=Encoder_Integral-Movement;                       //===����ң�������ݣ�����ǰ������
    if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
    if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===�����޷�
    Velocity=Encoder*pid.Kp_speed+Encoder_Integral*pid.Ki_speed;                          //===�ٶȿ���
    //return 0;//�ȵ���ֱ��
    return Velocity/10;
}


/**************************************************************************
�������ܣ�ת��PD����
��ڲ��������ֱ����������ֱ�������Z��������
����  ֵ��ת�����PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//ת�����
{
    static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
    float Turn_Amplitude=148/Flag_sudu,Kp=42,Kd=0;
    //=============ң��������ת����=======================//
    if(1==Flag_Left||1==Flag_Right)                      //��һ������Ҫ�Ǹ�����תǰ���ٶȵ����ٶȵ���ʼ�ٶȣ�����С������Ӧ��
    {
        if(++Turn_Count==1)
            Encoder_temp=myabs(encoder_left+encoder_right);
        Turn_Convert=50/Encoder_temp;
        if(Turn_Convert<0.6)Turn_Convert=0.6;
        if(Turn_Convert>3)Turn_Convert=3;
    }
    else
    {
        Turn_Convert=0.9;
        Turn_Count=0;
        Encoder_temp=0;
    }
    if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
    else if(1==Flag_Right)	     Turn_Target+=Turn_Convert;
    else Turn_Target=0;

    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת���ٶ��޷�
    if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
    if(Flag_Qian==1||Flag_Hou==1)  Kd=1;
    else Kd=0;   //ת���ʱ��ȡ�������ǵľ��� �е�ģ��PID��˼��
    //=============ת��PD������=======================//
    Turn=-Turn_Target*Kp -gyro*Kd;                 //===���Z�������ǽ���PD����
    return Turn;
}