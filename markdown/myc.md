

[toc]

### myc ###

打开 fopen

文件操作 fscanf，fprintf，fread，fwrite

关闭 fclose（不进行则前面操作无效）

exit(0)终止程序

### fopen 

格式 

file*fp；

fp=fopen（“文件名”，“打开方式”）；

打开出错地址返回null

成功返回文件主地址

例如：fopen（“c:\\\file.c”，“r”）；

### 打开方式

只读：r，rb

只写：w，wb

读写：r+,w+,a+,rb+,wb+,ab

追加：a,ab

### fclose

fclose(文件指针)；

### 特点

在一般格式下加f代表对文件操作

### fgetc fputc

char ch;

fgetc(fp);

fputc(ch,fp);

putw（，）读汉字

getw（）输汉字

### feof

判断文件是否结束 

feof(fp);

未结束返回0，结束返回ture；

EOF=-1（在stdio里是）；

啥也没有时指针指向feof的第一个字符，会出现判断错误

### fprintf fscanf

fgets（字符数组名，字符个数，文件指针）

fputs（字符数组名，文件指针）

fprintf(文件指针,"格式"，输出列表)；

fscanf(文件指针,"格式"，输出列表)；

### fread和fwrite

fread（数据存放地址，大小，多少，文件指针）；

fwrite一致

### argv

1. 运行处的参数，写入变量后运行即可
2. 设置cmd弹窗，找到，目录，写入文件名和变量(用空格隔开)

### rewind

rewind(fp);

返回文件开头

### ftell

得到当前位置

ftell（文件指针）

返回相对于文件开头（为0）的位移量（字节数）

返回值为-1L表示出错

### fseek

fseek（文件指针，位移量，起始点）

fseek（fp，100L，0）

表示移到第101个字节。

