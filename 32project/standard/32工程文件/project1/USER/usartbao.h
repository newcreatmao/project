#ifndef __USARTBAO_H
#define __USARTBAO_H_
extern uint8_t TXPacket[];
extern uint8_t RXPacket[];
void USART_INIT_baoRX();
void sendbyte1(uint8_t byte);
void sendarray1(uint8_t *array,uint16_t length);
void sendpacket1();
uint8_t GETRX_flag1(void);
#endif