#include "my_spi.h"
#include "my_gpio.h"
#include "my_afio.h"

typedef enum
{
#ifdef HAVE_SPI1
    //
    SPI1_CSPin = A4,
    SPI1_CLKPin = A5,
    SPI1_MISOPin = A6,
    SPI1_MOSIPin = A7,
#endif
#ifdef HAVE_SPI2
    //
    SPI2_CSPin = B12,
    SPI2_CLKPin = B13,
    SPI2_MISOPin = B14,
    SPI2_MOSIPin = B15,
#endif
#ifdef HAVE_SPI3
    //
    SPI3_CSPin = A15,
    SPI3_CLKPin = B3,
    SPI3_MISOPin = B4,
    SPI3_MOSIPin = B5,
#endif
    SPI_Pin_END
} SPI_Pin_enum;

typedef struct
{
    Pin_enum cs;
    Pin_enum clk;
    Pin_enum miso;
    Pin_enum mosi;
} SPI_Pins;

void spi_select_pin(SPI_enum spi, SPI_Pins *pins)
{
    switch (spi)
    {
#ifdef HAVE_SPI1
    case SPI_1:
        pins->cs = (Pin_enum)SPI1_CSPin, pins->clk = (Pin_enum)SPI1_CLKPin, pins->miso = (Pin_enum)SPI1_MISOPin, pins->mosi = (Pin_enum)SPI1_MOSIPin;
        return;
#endif
#ifdef HAVE_SPI2
    case SPI_2:
        pins->cs = (Pin_enum)SPI2_CSPin, pins->clk = (Pin_enum)SPI2_CLKPin, pins->miso = (Pin_enum)SPI2_MISOPin, pins->mosi = (Pin_enum)SPI2_MOSIPin;
        return;
#endif
#ifdef HAVE_SPI3
    case SPI_3:
        pins->cs = (Pin_enum)SPI3_CSPin, pins->clk = (Pin_enum)SPI3_CLKPin, pins->miso = (Pin_enum)SPI3_MISOPin, pins->mosi = (Pin_enum)SPI3_MOSIPin;
        return;
#endif
    default:
        return;
    }
}

void spi_clock_enable(SPI_enum spi)
{
    switch (spi)
    {
#ifdef HAVE_SPI1
    case SPI_1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
        return;
#endif
#ifdef HAVE_SPI2
    case SPI_2:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
        return;
#endif
#ifdef HAVE_SPI3
    case SPI_3:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
        return;
#endif
    default:
        return;
    }
}

uint16_t spi_speed_count(SPI_enum spi, int speed)
{
    // int APB1Clk = 36000; //(khz)
    // int APB2Clk = 72000; //(khz)

    return SPI_BaudRatePrescaler_2;
}

void spi_pin_init(SPI_enum spi, SPI_MasterSlave_mode mode)
{
    SPI_Pins pins;
    spi_select_pin(spi, &pins);

    if (mode == SPI_Mode_Master)
    {
        afio_init(pins.clk, OUT_PP_AF);
        afio_init(pins.mosi, OUT_PP_AF);
        gpio_init(pins.miso, INPUT_PULLUP);
    }
    else
    {
        gpio_init(pins.clk, INPUT);
        gpio_init(pins.mosi, INPUT_PULLUP);
        afio_init(pins.miso, OUT_PP_AF);
    }
}

void spi_hard_init_fill(SPI_enum spi, SPI_MasterSlave_mode spi_mode, int speed, SPI_direction dir, SPI_datasize d_size, SPI_clock_mode c_mode, SPI_FB fb)
{
    spi_pin_init(spi, spi_mode);
    spi_clock_enable(spi);

    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Direction = dir;                                 //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = spi_mode;                                 //设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = d_size;                               //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = (uint32_t)c_mode & 0x0002;                //串行同步时钟的空闲状态为高电平
    SPI_InitStructure.SPI_CPHA = (uint32_t)c_mode & 0x0001;                //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                              // NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = spi_speed_count(spi, speed); //定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = fb;                                   //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;                               // CRC值计算的多项式
    SPI_Init((SPI_TypeDef *)spi, &SPI_InitStructure);                      //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

    SPI_Cmd((SPI_TypeDef *)spi, ENABLE); //使能SPI外设
}

Hardware_SPI spi_hard_init(SPI_enum spi, int speed, SPI_clock_mode c_mode)
{
    spi_hard_init_fill(spi, SPI_master, speed, SPI_2f, SPI_8b, c_mode, SPI_MBS);

    Hardware_SPI spi_struct;
    spi_struct.speed = speed;
    spi_struct.spi = spi;
    return spi_struct;
}

void spi_hard_start(Hardware_SPI *spi)
{
    gpio_write(spi->cs, 0);
}

void spi_hard_stop(Hardware_SPI *spi)
{
    gpio_write(spi->cs, 1);
}

uint16_t spi_hard_send_byte(Hardware_SPI *spi, uint8_t byte)
{
    while (SPI_I2S_GetFlagStatus((SPI_TypeDef *)spi->spi, SPI_I2S_FLAG_TXE) == RESET)
        ;
    SPI_I2S_SendData((SPI_TypeDef *)spi->spi, byte);
    return 0;
}

uint16_t spi_hard_send_bytes(Hardware_SPI *spi, uint8_t *buffer, int size)
{
    for (int i = 0; i < size; ++i)
    {
        spi_hard_send_byte(spi, buffer[i]);
    }
    return size;
}
uint16_t spi_hard_receive_byte(Hardware_SPI *spi)
{
    spi_hard_send_byte(spi, 0x00);
    while (SPI_I2S_GetFlagStatus((SPI_TypeDef *)spi->spi, SPI_I2S_FLAG_RXNE) == RESET)
        ;
    return SPI_I2S_ReceiveData((SPI_TypeDef *)spi->spi);
}
uint16_t spi_hard_receive_bytes(Hardware_SPI *spi, uint8_t *rec_buf, int size)
{
    for (int i = 0; i < size; ++i)
    {
        rec_buf[i] = spi_hard_receive_byte(spi);
    }
    return size;
}

size_t spi_hard_write_data(Hardware_SPI *spi, uint8_t byte)
{
    spi_hard_start(spi);
    spi_hard_send_byte(spi, byte);
    spi_hard_stop(spi);
    return 1;
}
size_t spi_hard_write_datas(Hardware_SPI *spi, const uint8_t *buf, size_t size)
{
    spi_hard_start(spi);
    for (int i = 0; i < size; ++i)
    {
        spi_hard_send_byte(spi, buf[i]);
    }
    spi_hard_stop(spi);
    return size;
}
size_t spi_hard_fill_datas(Hardware_SPI *spi, const uint8_t byte, size_t size)
{
    spi_hard_start(spi);
    for (int i = 0; i < size; ++i)
    {
        spi_hard_send_byte(spi, byte);
    }
    spi_hard_stop(spi);
    return size;
}
uint16_t spi_hard_receive_data(Hardware_SPI *spi)
{
    spi_hard_start(spi);
    uint8_t rec = spi_hard_receive_byte(spi);
    spi_hard_stop(spi);
    return rec;
}
size_t spi_hard_receive_datas(Hardware_SPI *spi, uint8_t *buf, size_t size)
{
    spi_hard_start(spi);
    for (int i = 0; i < size; ++i)
    {
        buf[i] = spi_hard_receive_byte(spi);
    }
    spi_hard_stop(spi);
    return size;
}

size_t spi_hard_write_data16(Hardware_SPI *spi, uint16_t byte)
{
    spi_hard_start(spi);
    spi_hard_send_byte(spi, (uint8_t)(byte >> 8));
    spi_hard_send_byte(spi, (uint8_t)byte);
    spi_hard_stop(spi);
    return 1;
}
size_t spi_hard_write_data16s(Hardware_SPI *spi, const uint16_t *buf, size_t size)
{
    spi_hard_start(spi);
    for (int i = 0; i < size; ++i)
    {
        spi_hard_send_byte(spi, (uint8_t)(buf[i] >> 8));
        spi_hard_send_byte(spi, (uint8_t)buf[i]);
    }

    spi_hard_stop(spi);
    return size;
}
size_t spi_hard_fill_data16s(Hardware_SPI *spi, uint16_t byte, size_t count)
{
    spi_hard_start(spi);
    for (int i = 0; i < count; ++i)
    {
        spi_hard_send_byte(spi, (uint8_t)(byte >> 8));
        spi_hard_send_byte(spi, (uint8_t)byte);
    }

    spi_hard_stop(spi);
    return count;
}
uint16_t spi_hard_receive_data16(Hardware_SPI *spi)
{
    spi_hard_start(spi);
    uint16_t rec = spi_hard_receive_byte(spi);
    rec <<= 8;
    rec |= spi_hard_receive_byte(spi);
    spi_hard_stop(spi);
    return rec;
}
size_t spi_hard_receive_data16s(Hardware_SPI *spi, uint16_t *buf, size_t size)
{
    spi_hard_start(spi);
    for (int i = 0; i < size; ++i)
    {
        buf[i] = spi_hard_receive_byte(spi);
        buf[i] <<= 8;
        buf[i] |= spi_hard_receive_byte(spi);
    }
    spi_hard_stop(spi);
    return size;
}
