#ifndef __CHUANGKOU_H
#define __CHUANGKOU_H
void USART_INIT_TX();
void sendbyte(uint8_t byte);
unsigned char revice();
void USART_INIT_interRX();
void USART_INIT_RX();
uint8_t GETRX_flag(void);
uint8_t GET_data(void);
//void USART1_IRQGandler(void);
#endif