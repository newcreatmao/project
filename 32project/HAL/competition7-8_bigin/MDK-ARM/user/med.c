#include "main.h"

uint8_t med(void){                                          //读取电平，返回信号
	HAL_GPIO_ReadPin(medcine_GPIO_Port,medcine_Pin);
	
	if(HAL_GPIO_ReadPin(medcine_GPIO_Port,medcine_Pin)==SET){
	return 1;																									//返回高电平
	}
	else return 0;																						//返回低电平
}
