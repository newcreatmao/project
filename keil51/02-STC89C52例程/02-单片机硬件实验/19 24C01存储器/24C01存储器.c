/***************************************************************************
ʵ�����ƣ� 24C01�洢����дʵ��

ʵ��ģ��:  51��Ƭ�����İ塢EEPROM����Һ����ʾ����1602��

ʵ����ߣ�  51��Ƭ�����İ�------EEPROM��
					P3.6 --------- SCL
					P3.7 --------- SDA
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
����������	��������д��24C01оƬ�ڣ��ٽ����������������LCD��ʾ
			��Ϊ֤��2401�����ã�ȥ��2401���ߣ����ܶ���MCUд�������� ��

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define OP_READ  0xa1          // ������ַ�Լ���ȡ����
#define OP_WRITE 0xa0          // ������ַ�Լ�д�����

sbit  LCM_RS = P2^0;			 //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

sbit SDA = P3^7;    
sbit SCL = P3^6;

#define LCM_Data P0
#define Busy 0x80 //���ڼ��LCM״̬���е�Busy��ʶ

unsigned char code  dis_code[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//Һ����ʾ�ַ����                            

unsigned char shift;
unsigned char count=0;

/**********************************************************/
/*******************24C01������غ���**********************/
/**********************************************************/
//**********************************************************
//��ʱ�ӳ���
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

//**********************************************************
//��ʱ�ӳ���
void Delay_ms(uint ms) 
{
    uchar k;
    while(ms--)
       {
           for(k = 0; k < 120; k++);
       }
}

//**********************************************************
// ��ʼλ
void Start()
{
   SDA = 1;
   SCL = 1;
   delayNOP();
   SDA = 0;
   delayNOP();
   SCL = 0;
}

//**********************************************************
//  ֹͣλ
void stop()
{
   SDA = 0;
   delayNOP();
   SCL = 1;
   delayNOP();
   SDA = 1;
}

//**********************************************************
// ��AT24C01�������ݵ�MCU
uchar read()
{
   uchar i,read_data;
   for(i = 0; i < 8; i++)
   {
     SCL = 1;
     read_data <<= 1;
     read_data |= SDA;
     SCL = 0;
   }
   return(read_data);
}

//**********************************************************
// ��MCUд�����ݵ�AT24C01
bit write(uchar write_data) 
{
    uchar i;
    bit ack_bit;
    for(i = 0; i < 8; i++)  // ѭ������8��λ
       {
          SDA = (bit)(write_data & 0x80);
          _nop_();
          SCL = 1;
          delayNOP();
          SCL = 0;
          write_data <<= 1;
       }
    SDA = 1;   // ��ȡӦ��
    delayNOP();
    SCL = 1;
    delayNOP();
    ack_bit = SDA;
    SCL = 0;
    return ack_bit; // ����AT24C01Ӧ��λ
}

//**********************************************************
// ��ָ����ַaddr��д������write_data
void write_byte(uchar addr, uchar write_data)
{
    Start();
    write(OP_WRITE);
    write(addr);
    write(write_data);
    stop();
    Delay_ms(10);  // д������
}

//**********************************************************
// �ڵ�ǰ��ַ��ȡ
uchar read_current()
{
    uchar read_data;
    Start();
    write(OP_READ);
    read_data = read();
    stop();
    return read_data;
}

//**********************************************************
// ��ָ����ַ��ȡ
uchar read_random(uchar random_addr)
{
   Start();
   write(OP_WRITE);
   write(random_addr);
   return(read_current());
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
    LCM_E = 0; //�������ٶ�̫�߿���������С����ʱ
    LCM_E = 0; //��ʱ
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
	WriteCommandLCM(position|0x80);	//����ָ��=80+��ַ��(00H~27H,40H~67H)
}

void LCMInit(void) //LCM��ʼ��
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
    WriteCommandLCM(0x06,1); // ��ʾ����ƶ�����
    WriteCommandLCM(0x0C,1); // ��ʾ�����������
}

/**********************************************************/
//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF; //����X���ܴ���15��Y���ܴ���1
    if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
    X |= 0x80; //���ָ����
    WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
    WriteDataLCM(DData);
}

/**********************************************************/
//**********************************************************
main()
{
	unsigned char i,j,x,y,temp=0,data_in=0;
	unsigned char Dis[]="Addr:00  Data:00";      //�趨��ʾ��ʽ
	LCMInit();    //LCM��ʼ��
	SDA = 1;
	SCL = 1;  		   
	while(1)
	{				       		   
		for(i = 0 ; i <128; i++)	
		{
			write_byte(i,data_in);     //д����ʾ���뵽AT24C01
			
			temp=i;                    //д��AT24C01���ݵĵ�ַ
			
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
			
			temp=read_random(i);      //��ȡAT24C01����
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
//***********************************************************
