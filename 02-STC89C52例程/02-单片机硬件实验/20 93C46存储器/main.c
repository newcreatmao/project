/***************************************************************************
ʵ�����ƣ� 93C46�洢����дʵ��

ʵ��ģ��:  51��Ƭ�����İ塢EEPROM����Һ����ʾ����1602��

ʵ����ߣ�  51��Ƭ�����İ�------EEPROM��
					P3.4 --------- DO
					P3.5 --------- DI
					P3.6 --------- CLK
					P3.7 --------- CS
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
����������	��������д��93C46оƬ�ڣ��ٽ����������������LCD��ʾ
			��Ϊ֤��2401�����ã�ȥ��2401���ߣ����ܶ���MCUд�������ݣ�
			
			ע�⣺�ڲ�����д������֮ǰ��������д��EWENָ�����8λģʽ

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg52.h>
#include <intrins.h>

sbit CS  = P3^7;     //���幦������
sbit SCL = P3^6;
sbit DI  = P3^5;
sbit DO  = P3^4;

sbit  LCM_RS = P2^0; //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 	//���ڼ��LCM״̬���е�Busy��ʶ

unsigned char code  dis_code[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//Һ����ʾ�ַ����                            

/**********************************************************/
/*******************93C46��غ���**************************/
/**********************************************************/

/**********************************************************/
//93C46�˿ڳ�ʼ��
void INIT_93C46(void)
{
    CS=0;//��ʼ���˿�
    SCL=0;
    DI=1;
    DO=1;
}

/**********************************************************/
//д������
void Write46(unsigned char indata)               
{
   unsigned char i;
   for(i = 0; i < 8; i++)
   {
      DI = (bit)(indata & 0x80);// �������λ
      SCL = 1;
      indata <<= 1;
      SCL = 0;      
   }
   DI = 1;
}

/**********************************************************/
// ��������
unsigned char Read46(void)         
{
   unsigned char i, out_data;
   for(i = 0; i < 8; i++)
   {
      SCL = 1;
      out_data <<= 1;
      SCL = 0;
      out_data |= (unsigned char)DO;
   }
   return(out_data);
}

/**********************************************************/
//����һ��λ
void Sendbit (bit IO)            
{
    DI=IO;            //ȷ��д��bit 0��bit 1
    SCL=1;SCL=0;      //д������
}

/*��д���ܲ�������*/

/**********************************************************/
//�趨 д���� ���ܺ����� ������ 1 00 11XXXXX
void EWEN46 (void)            
{
    _nop_();
    CS=1;               //Ƭѡ
    Sendbit(1);         //������ʼλ
    Sendbit(0);         //���Ͳ������λ
    Write46(0x60);      //����ַ��Ϣ��������λ���ϣ�һ����
    CS=0;               //ȡ��Ƭѡ
}

/**********************************************************/
//�趨 д��ֹ ���ܺ����� ������ 1 00 00XXXXX
void EWDS46 (void)            
{
    _nop_();
    CS=1;
    Sendbit(1);
    Sendbit(0);
    Write46(0x00);
    CS=0;
}

/**********************************************************/
//�趨 ����ȫ�� ���ܺ����������� 1 00 10XXXXX
void ERAL46 (void)            
{
    _nop_();
    CS=1;
    Sendbit(1);
    Sendbit(0);
    Write46(0x40);
    CS=0;
}

//�û��ӿڹ��ܺ���

/**********************************************************/
//ָ����ַ����ȡһ���ֽڣ������� 1 10 XXXXXXX
char ReadByte46 (unsigned char addr)       
{                                      //��λ��ַ��Ӧ8bitģʽ    
    CS=SCL=0;
    CS=1;                              //Ƭѡ��
    _nop_();                           //��ʱ
    Sendbit(1);                        //���Ϳ�ʼλ
    Sendbit(1);                        //���Ͳ������λ
    Write46(0x7F&addr);                //���ϵ�ַ��������λ����
    addr=Read46();                     //��ȡ����
    CS=0;_nop_();                      //�ر�Ƭѡ
    return (addr);                     //��������
}

/**********************************************************/
//ָ����ַ��д��һ���ֽڣ������� 1 01 XXXXXXX
void WriteByte46 (unsigned char addr,char thedata)    
{                                            //��λ��ַ��Ӧ8bitģʽ
    unsigned int time=0;                     //���峬ʱ����
    unsigned char i=0;                       //����д��ѭ������
    do{                                      //��ʼ����д��ѭ�����ɹ�д������
        CS=SCL=0;                                
        CS=1;                                //��Ƭѡ�ź�
        EWEN46();                            //��д������
        _nop_();                             //��ʱ
        CS=1;                                //���¿�Ƭѡ
        _nop_();
        Sendbit(1);                          //���Ϳ�ʼ��
        Sendbit(0);                          //���Ͳ������λ
        Write46(0x80|addr);                  //���ϲ������λ����λ��ַ
        Write46(thedata);                    //д������
        CS=0;                                //�ر�Ƭѡ
        _nop_();                             //��ʱ
        CS=1;                                //�ؿ�Ƭѡ
        do                                   //æ�б�
        {
            if(time>500) break;              //����ڼ������⣬��ʱ�˳�
            time++;
        }while(!DO);                         //�������׼��������ȡ��ѭ��
        CS=0;                                //�ر�Ƭѡ
        if(ReadByte46(addr)==thedata) break; //�ж�д���Ƿ���ȷ����ȷ�˳�ѭ��������д������
        i++;
    }while(i<3);                             //д�������Զ��˳�
}

/**********************************************************/
// ��ʱ�ӳ���
void delayms(unsigned int ms)   
{                  
   unsigned char i;
   while(ms--)
   {
      for(i = 0; i < 120; i++);
   }
}

/**********************************************************/
/*******************LCM1602��غ���************************/
/**********************************************************/
//��״̬
////////////////////////////////////////////////////////////////////////////
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF; 
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    while (LCM_Data & Busy); //���æ�ź�
    return(LCM_Data);
    LCM_E = 0;
}


/**********************************************************/
//5ms��ʱ
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

/**********************************************************/
//д����
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //���æ
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; 		//�������ٶ�̫�߿���������С����ʱ
    LCM_E = 0; 		//��ʱ
    LCM_E = 1;
    LCM_E = 0;
}

/**********************************************************/
//дָ��
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
    if (BuysC) ReadStatusLCM(); //������Ҫ���æ
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0; 
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1; 
    LCM_E = 0;
}

/**********************************************************/
//������
unsigned char ReadDataLCM(void)
{
    LCM_RS = 1; 
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    return(LCM_Data);
    LCM_E = 0;
}

/**********************************************************/
//LCD����ָ��λ�ó���
void LCM_pos(char position)
{                  
   WriteCommandLCM(position|0x80);   //����ָ��=80+��ַ��(00H~27H,40H~67H)
}

/**********************************************************/
//LCM��ʼ��
void LCMInit(void) 
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //������ʾģʽ���ã������æ�ź�
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 

    WriteCommandLCM(0x38,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
    WriteCommandLCM(0x08,1); //�ر���ʾ
    WriteCommandLCM(0x01,1); //��ʾ����
    WriteCommandLCM(0x06,1); //��ʾ����ƶ�����
    WriteCommandLCM(0x0C,1); //��ʾ�����������
}

/**********************************************************/
//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF;         //����X���ܴ���15��Y���ܴ���1
    if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
    X |= 0x80;        //���ָ����
    WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
    WriteDataLCM(DData);
}

/**********************************************************/
main()
{
    unsigned char i,j,x,y,temp=0,data_in=0;
    unsigned char Dis[]="Addr:00  Data:00";      //�趨��ʾ��ʽ
    LCMInit();    	//LCM��ʼ��
    INIT_93C46(); 	//93C46�˿ڳ�ʼ��
    EWEN46();       // ʹ��д�����
    ERAL46();       // ����ȫ������*/
    while(1)
    {                            
       for(i = 0 ; i <128; i++)   
          {
              WriteByte46(i,data_in);     //д����ʾ���뵽AT93C46

              temp=i;                    //д��AT93C46���ݵĵ�ַ

              x=temp%16;                 //��ȡ��ַ��λ
              Dis[6]=dis_code[x];
              y=temp>>4;                 //��ȡ��ַ��λ
              Dis[5]=dis_code[y];
              x=data_in%16;              //��ȡ���ݵ�λ
              Dis[15]=dis_code[x];
              y=data_in>>4;              //��ȡ���ݸ�λ
              Dis[14]=dis_code[y];
              for(j=0;j<16;j++)
                 {
                     DisplayOneChar(j,0,Dis[j]);//�ڵ�һ����ʾ����д��ĵ�ַ������
                 }

              temp=ReadByte46(i);      	//��ȡAT93C46����
              x=i%16;                   //��ȡ��ַ��λ
              Dis[6]=dis_code[x];
              y=i>>4;                   //��ȡ��ַ��λ
              Dis[5]=dis_code[y];
              x=temp%16;                //��ȡ���ݵ�λ
              Dis[15]=dis_code[x];
              y=temp>>4;                //��ȡ���ݸ�λ
              Dis[14]=dis_code[y];
              for(j=0;j<16;j++)
                  {
                     DisplayOneChar(j,1,Dis[j]);//�ڵڶ�����ʾ���ζ�ȡ�ĵ�ַ������
                  }
              data_in++;
              if(data_in==128) data_in=0;
              delayms(1000);
              }
           }
}
/**********************************************************/
