/*************************************************************/
/********************* 24 ???????? *******************/
/*************************************************************/
/************************* ??:XHCH ************************/
/*************************************************************/
/******************* ????:2012?2?3? ******************/
/*************************************************************/
/***************************************************************************
????: ????????

????:  51??????????????????(1602)

????:  51??????------?????
				P1.0~P1.3 --------- ROW1~ROW4
				P1.4~P1.7 --------- LINE1~LINE4				
					
			51??????------?????(1602????)
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
????:	1602????????????,????????????

????:	2017.10.17
***************************************************************************/

#include <reg52.h>               

unsigned char  dis_buf;       //????
unsigned char  temp;
unsigned char  key=0;         //????

sbit  LCM_RS = P2^0; 		  //????
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //????LCM?????Busy??

unsigned char code  cdis1[ ] = {"computer user:"};//1 3 1 5
unsigned char Code1[]={'1','2','3','+','4','5','6','-','7','8','9','/','*','0','=','D'};
int j = 0;
unsigned char num[4]={'-','-','-','-'};
unsigned char Code[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
unsigned char a[4],b[4];
unsigned char yunsuanfu;
int num1=0,N1,x=0;
unsigned char flag=0;

/**********************************************************/
/*******************LCM1602????************************/
/**********************************************************/
//???
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF; 
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    while (LCM_Data & Busy); //?????
    return(LCM_Data);
    LCM_E = 0;
}


/**********************************************************/
//5ms??
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

/**********************************************************/
//???
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //???
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; //?????????????????
    LCM_E = 0; //??
    LCM_E = 1;
    LCM_E = 0;
}

/**********************************************************/
//???
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC?0??????
{
    if (BuysC) ReadStatusLCM(); //???????
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0; 
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1; 
    LCM_E = 0;
}

/**********************************************************/
//???
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
//LCM???
void LCMInit(void) 
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //????????,??????
    Delay5Ms();
	WriteCommandLCM(0x38,0);
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 

    WriteCommandLCM(0x38,1); //??????,???????????
    WriteCommandLCM(0x08,1); //????
    WriteCommandLCM(0x01,1); //????
    WriteCommandLCM(0x06,1); //????????
    WriteCommandLCM(0x0C,1); //????????
}

/**********************************************************/
//???????????
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF;         		//??X????15,Y????1
    if (Y) X |= 0x40; 		//???????????+0x40;
    X |= 0x80;        		//?????
    WriteCommandLCM(X, 0);  //????????,?????
    WriteDataLCM(DData);
}

/**********************************************************/
// ??????
void  keyscan(void)
 { 
	 int i,y=0,N2;
	 unsigned char charN1;
    P1=0xF0;                //?????,?????,????????0
	 temp=P1;               //?P1?       
    temp=temp&0xF0;
    temp=~((temp>>4)|0xF0);
    if(temp==1)
        key=0;
    else if(temp==2)
        key=1;
    else if(temp==4)
        key=2;
    else if(temp==8)
        key=3;
    P1=0x0F;                 //?????,?????,????????0  
	 temp=P1;                //?P1? 
    temp=temp&0x0F;
    temp=~(temp|0xF0);        
    if(temp==1)
        key=key+0;
    else if(temp==2)
        key=key+4;
    else if(temp==4)
        key=key+8;
    else if(temp==8)
        key=key+12;
    	
     dis_buf = key;	             //???????
     dis_buf = dis_buf&0x0f;


		 num[j]=Code1[key];
		 
		 if(Code1[key] == '+' || Code1[key] == '-' || Code1[key] == '*' || Code1[key] == '/')   //??????????
		 {
			 yunsuanfu = Code1[key];
			 N1 = num1;
			 num1 = 0;
		 }
		 else if(Code1[key]=='=')   //????
		 {
			 if(yunsuanfu == '+')
			 {
				  N1=N1+num1;
			 }
			 if(yunsuanfu == '-')
			 {
				 N1=N1-num1;
			 }
			 if(yunsuanfu == '*')
			 {
				  N1=N1*num1;
			 }
			 if(yunsuanfu == '/')
			 {
				 N1=N1/num1;
			 }
			
			 flag = j+1;
			 i = 0;
			 N2 = N1;
			 do                  //????????,?do-while??,???????
			 {
				 y++;
				 N2/=10;
			 }while(N2!=0);    //??????
			 do
			 {
				 DisplayOneChar(0x00 + j + y, 1, (N1 % 10) + '0');
				 N1 /= 10;
				 y--;
			 }while(N1!=0);
			 num1 = 0;
			 N1 = 0;
			
		 }
			else   //?????????,??0??ASCIL,??0????
			{
				num1=num1*10+(Code1[key]-'0');//???????0x30????????,????????????????
				 
			}

			j ++;
 }

/*************************************************************/
//???????
void  keydown(void)
 {  
  	P1=0xF0;
   Delay5Ms();
	if(P1!=0xF0)
	{
	  keyscan();
		Delay5Ms();
		while(P1==0xF0);
		Delay5Ms();
    }
 }

/*************************************************************/
// ???
main()
 {
    unsigned char m;
	 unsigned char i;
	unsigned char k;
    P0=0xFF;                    //?P0?
    P2=0xFF;                    //?P2?  
    Delay5Ms();                 //??
    LCMInit();                  //???LCD             
        
     m = 0;
    while(cdis1[m] != '\0')
     {                         //????
       DisplayOneChar(m,0,cdis1[m]);
       m++;
     }

     m = 0;

	  dis_buf = 0x2d;          		  //????"-"

    while(1)
    { 
       keydown();
			if (flag!=0 && j > flag)      //?????????
			{
				flag = 0;
				for(i = 0; i<16 ;i++)
			{
				 DisplayOneChar(0x00+i,1,' ');    //?????
					num1 = 0;
					x = 0;
			}
			j = 0;
			}
			else
				{
					for(i = 0; i<j ;i++)
					{
						DisplayOneChar(0x00+i,1,num[i]);    //?????
					}
			
				}
  }  
}		

/************************************************************/