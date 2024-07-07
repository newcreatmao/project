#ifndef __LCD1602_H__
#define __LCD1602_H__

//用户调用函数：
void myinit();
void mychar(unsigned char Line,unsigned char Column,char Char);
void mystring(unsigned char Line,unsigned char Column,char *String);
void pow(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void number(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void hex(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void bin(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif
