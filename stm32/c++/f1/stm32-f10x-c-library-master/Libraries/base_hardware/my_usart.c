/**************************************************************************
 * @brief       : STM32 USART
 * @author      : 龚为玮(1461041096)
 * @copyright   : 版权信息
 * @version     : v1.0
 * @note        : 无
 * @history     : 2021年11月20日：创建文件
 *                2021年11月22日：完成串口初始化功能、串口基础write功能
 *                               并对UART1进行了输出测试，测试通过
 *                2021年11月22日：添加注释
 *                2021年11月23日：对UART2~UART5进行了输出测试，测试通过
 *                2021年12月3日： 完成了串口接收相关接口，对UART1进行了测试
 *                2021年12月13日：发现UART4和UART5无法接收，原因不明
 *                2021年12月14日：解决了13日发现的问题，目前所有串口经过测试输入输
 *                               出可用
 *                2022年10月23日：增加了UART1~4 DMA输出功能，UART5不支持DMA
 ***************************************************************************/
#include "my_usart.h"
#include "string.h"

/**
 * @brief 串口默认引脚 \n
 *UART1_TX：串口1TX引脚，UART1_RX：串口1RX引脚，以此类推
 */
typedef enum
{
#ifdef HAVE_SERIAL1
  UART1_TX = A9,
  UART1_RX = A10,
#endif
#ifdef HAVE_SERIAL2
  UART2_TX = A2,
  UART2_RX = A3,
#endif
#ifdef HAVE_SERIAL3
  UART3_TX = B10,
  UART3_RX = B11,
#endif
#ifdef HAVE_SERIAL4
  UART4_TX = C10,
  UART4_RX = C11,
#endif
#ifdef HAVE_SERIAL5
  UART5_TX = C12,
  UART5_RX = D2,
#endif
  UARTn_Pin_End //占位，没用
} UART_pin;

/*************************************************************************
 * @brief   初始化串口
 * @param[in]	uart 要初始化的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @param[in] baudrate 串口通信波特率
 * @return 无
 * @note  该函数默认使用 8N1(8数据位，无校验位，1位停止位)模式，可在 my_uart.h中
 *        对应宏进行修改
 * @example uart_init(UART1, 115200) 初始化 UART1 并使能，波特率为115200
 * @history 2021-11-22：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
void uart_init(UART_enum uart, uint32_t baudrate)
{
  Pin_enum uart_tx, uart_rx;
  uint8_t USARTx_IRQn;
  switch (uart)
  {
#ifdef HAVE_SERIAL1
  case UART_1:
    uart_tx = (Pin_enum)UART1_TX, uart_rx = (Pin_enum)UART1_RX;
    memset((void *)&UART1_recbuf, 0, sizeof(UART1_recbuf));
    USARTx_IRQn = USART1_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL2
  case UART_2:
    uart_tx = (Pin_enum)UART2_TX, uart_rx = (Pin_enum)UART2_RX;
    memset((void *)&UART2_recbuf, 0, sizeof(UART2_recbuf));
    USARTx_IRQn = USART2_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL3
  case UART_3:
    uart_tx = (Pin_enum)UART3_TX, uart_rx = (Pin_enum)UART3_RX;
    memset((void *)&UART3_recbuf, 0, sizeof(UART3_recbuf));
    USARTx_IRQn = USART3_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL4
  case UART_4:
    uart_tx = (Pin_enum)UART4_TX, uart_rx = (Pin_enum)UART4_RX;
    memset((void *)&UART4_recbuf, 0, sizeof(UART4_recbuf));
    USARTx_IRQn = UART4_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL5
  case UART_5:
    uart_tx = (Pin_enum)UART5_TX, uart_rx = (Pin_enum)UART5_RX;
    memset((void *)&UART5_recbuf, 0, sizeof(UART5_recbuf));
    USARTx_IRQn = UART5_IRQn;
    break;
#endif
  default:
    return;
  }
  //获取UART对应引脚

  gpio_init(uart_rx, INPUT);
  afio_init(uart_tx, OUT_PP_AF);
  //初始化UART RX、TX引脚

  if (uart == UART_1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  }
  else
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 << (((uint32_t)uart - (uint32_t)UART_2) / 0x0400), ENABLE);
  }
  //使能UART时钟

  USART_InitTypeDef uart_inittype;
  uart_inittype.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;           //开启TX、RX模式
  uart_inittype.USART_BaudRate = baudrate;                            //设置波特率
  uart_inittype.USART_StopBits = DEFAULT_UART_STOPBITS;               //设置停止位
  uart_inittype.USART_Parity = DEFAULT_UART_PARITY;                   //设置校验位
  uart_inittype.USART_WordLength = DEFAULT_UART_WORDLENGTH;           //设置数据位长度
  uart_inittype.USART_HardwareFlowControl = DEFAULT_UART_FLOWCONTROL; //设置硬件流控

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能

  USART_Init((USART_TypeDef *)uart, &uart_inittype);            //初始化UART
  USART_Cmd((USART_TypeDef *)uart, ENABLE);                     //使能UART
  USART_ITConfig((USART_TypeDef *)uart, USART_IT_RXNE, ENABLE); //开启ENABLE中断
  NVIC_Init(&NVIC_InitStructure);                               //根据指定的参数初始化VIC寄存器

  USART_ClearFlag((USART_TypeDef *)uart, USART_FLAG_TC);
  uart_write_byte(uart, 0);
}

void uart_deinit(UART_enum uart)
{
  if (uart == UART_1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 << (((uint32_t)uart - (uint32_t)UART_2) / 0x0400), DISABLE);
  }
  //关闭时钟

  USART_Cmd((USART_TypeDef *)uart, DISABLE);                     //关闭串口
  USART_ITConfig((USART_TypeDef *)uart, USART_IT_RXNE, DISABLE); //关闭DISABLE中断
}

/*****************************串口输出相关接口*****************************/

/*************************************************************************
 * @brief   串口输出一个字节数据
 * @param[in]	uart 要输出字节的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @param[in] data 输出的字节数据
 * @return 无
 * @note  调用前应先对串口进行初始化
 * @example uart_write_byte(UART1, 'a') 串口1输出字节数据'a'
 * @history 2021-11-22：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
inline void uart_write_byte(UART_enum uart, uint8_t data)
{
  USART_SendData((USART_TypeDef *)uart, (uint16_t)data);
  while (USART_GetFlagStatus((USART_TypeDef *)uart, USART_FLAG_TC) == RESET)
    ;
}

/*************************************************************************
 * @brief   串口输出二进制数据(如输出结构体、二进制数据)
 * @param[in]	uart 要输出字节的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @param[in] buf 二进制数据指针
 * @param[in] len 二进制数据长度
 * @return 无
 * @note  调用前应先对串口进行初始化，调用时应注意二进制数据长度，不要越界！
 * @example uart_write_buffer(UART1, buf, 10)
 * @history 2021-11-22：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
void uart_write_buffer(UART_enum uart, const uint8_t *buf, int len)
{
  for (int i = 0; i < len; i++)
  {
    uart_write_byte(uart, (uint16_t)buf[i]);
  }
}

/*************************************************************************
 * @brief   串口输出字符串
 * @param[in]	uart 要输出字符串的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @param[in] str 要输出的字符串
 * @return 无
 * @note  调用前应先对串口进行初始化
 * @example uart_write_string(UART_1, "hello world")；串口1打印 hello world
 * @history 2021-11-22：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
void uart_write_string(UART_enum uart, const char *str)
{
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    uart_write_byte(uart, (uint16_t)str[i]);
  }
}

/*****************************串口接收相关接口*****************************/

/*************************************************************************
 * @brief   选择串口接收对应的缓冲区
 * @param[in]	uart 要接收字符串的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @return 串口接收缓冲区指针
 * @note  内部调用
 * @history 2021-12-2：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
__rec_buf *select_buf(UART_enum uart)
{
  switch (uart)
  {
#ifdef HAVE_SERIAL1
  case UART_1:
    return &UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
  case UART_2:
    return &UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
  case UART_3:
    return &UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
  case UART_4:
    return &UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
  case UART_5:
    return &UART5_recbuf;
#endif
  default:
    return 0;
  }
}

/*************************************************************************
 * @brief   获取串口缓冲区接收数据长度
 * @param[in]	uart 要接收字符串的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @return 串口缓冲区接收到数据的长度
 * @note   串口缓冲区最大为256个字节
 * @history 2021-12-2：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
uint16_t uart_rec_size(UART_enum uart)
{
  __rec_buf *uart_recbuf = select_buf(uart);
  return uart_recbuf->data_size;
}

/*************************************************************************
 * @brief   从串口缓冲区读取一个数据
 * @param[in]	uart 要接收字符串的串口 (可选择的值在 my_uart.h UART_enum枚举中)
 *            此参数可以是以下值之一:
 *              UART1 UART2 UART3 UART4 UART5
 * @return 读取到的值
 * @note   该函数为阻滞函数
 * @history 2021-12-2：创建，完成功能并使用 USART1 进行测试，测试通过
 ************************************************************************/
uint8_t uart_read_byte(UART_enum uart)
{
  __rec_buf *uart_recbuf = select_buf(uart);
  while (uart_recbuf->data_size == 0) //等待串口缓冲区接收到数据
    ;
  uint8_t res = uart_recbuf->buf[uart_recbuf->read_index++];
  uart_recbuf->data_size--;
  return res;
}

/***********************串口接收中断***************************************/
#ifdef HAVE_SERIAL1
__rec_buf UART1_recbuf;
void USART1_IRQHandler(void)
{
  if (USART_GetITStatus(USART1, USART_IT_RXNE))
  {
    if (UART1_recbuf.data_size >= 256)
    {
      // uart_write_string(UART_1, "UART1 recbuf fill!\r\n");
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
      return;
    }
    uint16_t recdata = USART_ReceiveData(USART1);
    UART1_recbuf.buf[UART1_recbuf.write_index++] = (uint8_t)recdata;
    UART1_recbuf.data_size++;
  }
  USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
#endif

#ifdef HAVE_SERIAL2
__rec_buf UART2_recbuf;
void USART2_IRQHandler(void)
{
  if (USART_GetITStatus(USART2, USART_IT_RXNE))
  {
    uint16_t recdata = USART_ReceiveData(USART2);
    if (UART2_recbuf.data_size >= 256)
    {
      // uart_write_string(UART_2, "UART2 recbuf fill!\r\n");
      USART_ClearITPendingBit(USART2, USART_IT_RXNE);
      return;
    }
    UART2_recbuf.buf[UART2_recbuf.write_index++] = (uint8_t)recdata;
    UART2_recbuf.data_size++;
  }
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}
#endif

#ifdef HAVE_SERIAL3
__rec_buf UART3_recbuf;
void USART3_IRQHandler(void)
{
  if (USART_GetITStatus(USART3, USART_IT_RXNE))
  {
    uint16_t recdata = USART_ReceiveData(USART3);
    if (UART3_recbuf.data_size >= 256)
    {
      // uart_write_string(UART_3, "UART3 recbuf fill!\r\n");
      USART_ClearITPendingBit(USART3, USART_IT_RXNE);
      return;
    }
    UART3_recbuf.buf[UART3_recbuf.write_index++] = (uint8_t)recdata;
    UART3_recbuf.data_size++;
  }
  USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
#endif

#ifdef HAVE_SERIAL4
__rec_buf UART4_recbuf;
void UART4_IRQHandler(void)
{
  if (USART_GetITStatus(UART4, USART_IT_RXNE))
  {
    uint16_t recdata = USART_ReceiveData(UART4);
    if (UART4_recbuf.data_size >= 256)
    {
      // uart_write_string(UART_4, "UART1 recbuf fill!\r\n");
      USART_ClearITPendingBit(UART4, USART_IT_RXNE);
      return;
    }
    UART4_recbuf.buf[UART4_recbuf.write_index++] = (uint8_t)recdata;
    UART4_recbuf.data_size++;
  }
  USART_ClearITPendingBit(UART4, USART_IT_RXNE);
}
#endif

#ifdef HAVE_SERIAL5
__rec_buf UART5_recbuf;
void UART5_IRQHandler(void)
{
  if (USART_GetITStatus(UART5, USART_IT_RXNE))
  {
    uint16_t recdata = USART_ReceiveData(UART5);
    if (UART5_recbuf.data_size >= 256)
    {
      // uart_write_string(UART_5, "UART1 recbuf fill!\r\n");
      USART_ClearITPendingBit(UART5, USART_IT_RXNE);
      return;
    }
    UART5_recbuf.buf[UART5_recbuf.write_index++] = (uint8_t)recdata;
    UART5_recbuf.data_size++;
  }
  USART_ClearITPendingBit(UART5, USART_IT_RXNE);
}
#endif

//*****************************************UART_DMA****************************************//
static uint32_t get_uart_dam_tx_ch(UART_enum uart)
{
  switch (uart)
  {
#ifdef HAVE_SERIAL1
  case UART_1:
    return (uint32_t)DMA1_Channel4;
#endif
#ifdef HAVE_SERIAL2
  case UART_2:
    return (uint32_t)DMA1_Channel7;
#endif
#ifdef HAVE_SERIAL3
  case UART_3:
    return (uint32_t)DMA1_Channel2;
#endif
#ifdef HAVE_SERIAL4
  case UART_4:
    return (uint32_t)DMA2_Channel5;
#endif
#ifdef HAVE_SERIAL5
  case UART_5:
  default:
    return 0x0000;
#endif
  }
	return 0x0000;
}

static uint32_t get_uart_dma_tx_req(UART_enum uart)
{
  switch (uart)
  {
#ifdef HAVE_SERIAL1
  case UART_1:
    return (uint32_t)DMA1_Channel4_IRQn;
#endif
#ifdef HAVE_SERIAL2
  case UART_2:
    return (uint32_t)DMA1_Channel7_IRQn;
#endif
#ifdef HAVE_SERIAL3
  case UART_3:
    return (uint32_t)DMA1_Channel2_IRQn;
#endif
#ifdef HAVE_SERIAL4
  case UART_4:
    return (uint32_t)DMA2_Channel4_5_IRQn;
#endif
#ifdef HAVE_SERIAL5
  case UART_5:
  default:
    return 0x0000;
#endif
  }
	return 0x0000;
}

void uart_dma_init(UART_enum uart)
{
#ifdef HAVE_SERIAL5
  if (UART_5 == uart) // UART5没有DMA
    return;
#endif
  DMA_InitTypeDef DMA_InitType;
  NVIC_InitTypeDef NVIC_InitStructure;
  DMA_Channel_TypeDef *dma_ch = (DMA_Channel_TypeDef *)get_uart_dam_tx_ch(uart);
#ifdef HAVE_SERIAL4
  if (UART_4 == uart)
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE); //使能DMA2时钟(UART4)
  else
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA1时钟(UART1~UART3)
#endif
  //初始化DMA RAW->USART
  DMA_DeInit(dma_ch);                                                        //将DMA的通道7寄存器重设为缺省值
  DMA_InitType.DMA_PeripheralBaseAddr = (u32)(&((USART_TypeDef *)uart)->DR); //启动传输前装入实际RAM地址
  DMA_InitType.DMA_MemoryBaseAddr = 0;                                       //设置发送缓冲区首地址
  DMA_InitType.DMA_DIR = DMA_DIR_PeripheralDST;                              //数据传输方向，从内存发送到外设
  DMA_InitType.DMA_BufferSize = 0;                                           // DMA通道的DMA缓存的大小
  DMA_InitType.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                //外设地址寄存器不变
  DMA_InitType.DMA_MemoryInc = DMA_MemoryInc_Enable;                         //内存地址寄存器递增
  DMA_InitType.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;         //数据宽度为8位
  DMA_InitType.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;                 //数据宽度为8位
  DMA_InitType.DMA_Mode = DMA_Mode_Normal;                                   //工作在正常模式
  DMA_InitType.DMA_Priority = DMA_Priority_High;                             // DMA通道 x拥有高优先级
  DMA_InitType.DMA_M2M = DMA_M2M_Disable;                                    // DMA通道x没有设置为内存到内存传输
  DMA_Init(dma_ch, &DMA_InitType);                                           //对DMA通道7进行初始化                         //根据指定的参数初始化NVIC寄存器

  // DMA发送完成中断
  NVIC_InitStructure.NVIC_IRQChannel = (uint8_t)get_uart_dma_tx_req(uart); // NVIC通道设置
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;                //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                       //子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                          // IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);                                          //根据指定的参数初始化NVIC寄存器
  DMA_ITConfig(dma_ch, DMA_IT_TC, ENABLE);                                 //开USART2 Tx DMA中断

  //先关闭RAW->USART通道
  DMA_Cmd(dma_ch, DISABLE); //使DMA通道7停止工作

  //使能DMA-串口
  USART_DMACmd((USART_TypeDef *)uart, USART_DMAReq_Tx, ENABLE);
  // USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE); //开启串口DMA接收
}

//**********DMA中断请求**********//
#ifdef HAVE_SERIAL1
volatile uint8_t UART1_DMA_Tx_Status = 0; // DMA发送标准位
void DMA1_Channel4_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC4) != RESET) // DMA接收完成标志
  {
    DMA_ClearITPendingBit(DMA1_IT_TC4);     //清除中断标志
    USART_ClearFlag(USART1, USART_FLAG_TC); //清除串口的标志位
    DMA_Cmd(DMA1_Channel4, DISABLE);        //关闭USART TX DMA所指示的通道
    UART1_DMA_Tx_Status = 0;                //发送标志置0(关闭)
  }
}
#endif

#ifdef HAVE_SERIAL2
volatile uint8_t UART2_DMA_Tx_Status = 0; // DMA发送标准位
void DMA1_Channel7_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC7) != RESET) // DMA接收完成标志
  {
    DMA_ClearITPendingBit(DMA1_IT_TC7);     //清除中断标志
    USART_ClearFlag(USART2, USART_FLAG_TC); //清除串口的标志位
    DMA_Cmd(DMA1_Channel7, DISABLE);        //关闭USART TX DMA 所指示的通道
    UART2_DMA_Tx_Status = 0;                //发送标志置0(关闭)
  }
}
#endif

#ifdef HAVE_SERIAL3
volatile uint8_t UART3_DMA_Tx_Status = 0; // DMA发送标准位
void DMA1_Channel2_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC2) != RESET) // DMA接收完成标志
  {
    DMA_ClearITPendingBit(DMA1_IT_TC2);     //清除中断标志
    USART_ClearFlag(USART3, USART_FLAG_TC); //清除串口2的标志位
    DMA_Cmd(DMA1_Channel2, DISABLE);        //关闭USART2 TX DMA 所指示的通道
    UART3_DMA_Tx_Status = 0;                //发送标志置0(关闭)
  }
}
#endif

#ifdef HAVE_SERIAL4
volatile uint8_t UART4_DMA_Tx_Status = 0; // DMA发送标准位
void DMA2_Channel4_5_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA2_IT_TC5) != RESET) // DMA接收完成标志
  {
    DMA_ClearITPendingBit(DMA2_IT_TC5);    //清除中断标志
    USART_ClearFlag(UART4, USART_FLAG_TC); //清除串口的标志位
    DMA_Cmd(DMA2_Channel5, DISABLE);       //关闭USART TX DMA 所指示的通道
    UART4_DMA_Tx_Status = 0;               //发送标志置0(关闭)
  }
}
#endif

#ifdef HAVE_SERIAL5
// volatile uint8_t UART5_DMA_Tx_Status = 0; //uart5没有DMA
#endif
//**********DMA中断请求**********//

static volatile uint8_t *get_uart_dma_tx_status(UART_enum uart)
{
  switch (uart)
  {
#ifdef HAVE_SERIAL1
  case UART_1:
    return &UART1_DMA_Tx_Status;
#endif
#ifdef HAVE_SERIAL2
  case UART_2:
    return &UART2_DMA_Tx_Status;
#endif
#ifdef HAVE_SERIAL3
  case UART_3:
    return &UART3_DMA_Tx_Status;
#endif
#ifdef HAVE_SERIAL4
  case UART_4:
    return &UART4_DMA_Tx_Status;
#endif
#ifdef HAVE_SERIAL5
  case UART_5:
  default:
    return 0; // return busy
#endif
  }
  return 0;
}

void uart_dma_write_buffer(UART_enum uart, const uint8_t *buf, int len)
{
#ifdef HAVE_SERIAL5
  if(UART_5 == uart)
    uart_write_buffer(uart, buf, len);//UART5不支持DMA,改用普通方式发送!
#endif
  volatile uint8_t *dma_statu = get_uart_dma_tx_status(uart);
  DMA_Channel_TypeDef *dma_ch = (DMA_Channel_TypeDef *)get_uart_dam_tx_ch(uart);
  while (*dma_statu)
    ;                           //等待上一次发送完成（dma_statu为1即还在发送数据）
  *dma_statu = 1;               // 发送标志置1（启动发送）
  dma_ch->CMAR = (uint32_t)buf; //设置要发送的数据地址
  dma_ch->CNDTR = len;          //设置要发送的字节数目
  DMA_Cmd(dma_ch, ENABLE);      //开始DMA发送
}
//*****************************************UART_DMA****************************************//
