#include <regx52.h>

#if 0
#define DS1302_IO P3_4
#define DS1302_SCLK P3_6
#define DS1302_CE P3_5

//最低位为低表示w
#define second_cmd 0x80
#define minute_cmd 0x82
#define hour_cmd 0x84
#define day_cmd 0x86
#define month_cmd 0x88
#define week_cmd 0x8A
#define year_cmd 0x8C
#define wp_cmd 0x8E

#endif

#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E
extern unsigned char DS1302_Time[];

void init(void);
void write(unsigned char Command,Data);
unsigned char read(unsigned char com);
void settime(void);
void readtime(void);
