#include "main.h"

uint8_t med(void){                                          //��ȡ��ƽ�������ź�
	HAL_GPIO_ReadPin(medcine_GPIO_Port,medcine_Pin);
	
	if(HAL_GPIO_ReadPin(medcine_GPIO_Port,medcine_Pin)==SET){
	return 1;																									//���ظߵ�ƽ
	}
	else return 0;																						//���ص͵�ƽ
}
