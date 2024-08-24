#ifndef __MY_SPI_H
#define __MY_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "resources.h"
#include "stm32f10x_spi.h"
#include <stdio.h>

typedef enum
{
#ifdef HAVE_SPI1
    SPI_1 = (uint32_t)SPI1,
#endif
#ifdef HAVE_SPI2
    SPI_2 = (uint32_t)SPI2,
#endif
#ifdef HAVE_SPI3
    SPI_3 = (uint32_t)SPI3,
#endif
    SPI_END
} SPI_enum;

typedef enum
{
    SPI_master = SPI_Mode_Master,
    SPI_slave = SPI_Mode_Slave
} SPI_MasterSlave_mode;

typedef enum
{
    SPI_2f = SPI_Direction_2Lines_FullDuplex,
    SPI_2r = SPI_Direction_2Lines_RxOnly,
    SPI_1r = SPI_Direction_1Line_Rx,
    SPI_1t = SPI_Direction_1Line_Tx
} SPI_direction;

typedef enum
{
    SPI_8b = SPI_DataSize_8b,
    SPI_16b = SPI_DataSize_16b,
} SPI_datasize;

/*typedef enum
{
    SPI_36Mhz = SPI_BaudRatePrescaler_2,
    SPI_18Mhz = SPI_BaudRatePrescaler_4,
    SPI_9Mhz = SPI_BaudRatePrescaler_8,
    SPI_4Mhz = SPI_BaudRatePrescaler_16,
    SPI_2Mhz = SPI_BaudRatePrescaler_32,
    SPI_1Mhz = SPI_BaudRatePrescaler_64,
    SPI_576Khz = SPI_BaudRatePrescaler_128,
    SPI_288Khz = SPI_BaudRatePrescaler_256,
    SPI_144Khz
} SPI_speed;*/

typedef enum
{
    CS_hard = SPI_NSS_Hard,
    CS_soft = SPI_NSS_Soft
} SPI_CSmode;

typedef enum
{
    CPOL_LOW_CPHA_LOW = 0,
    CPOL_LOW_CPHA_HIGH = 1,
    CPOL_HIGH_CPHA_LOW = 2,
    CPOL_HIGH_CPHA_HIGH = 3,
} SPI_clock_mode;

typedef enum
{
    SPI_MBS = SPI_FirstBit_MSB,
    SPI_LBS = SPI_FirstBit_LSB
} SPI_FB;

typedef enum
{
    SPI_CRC_DEFAULT = 7
} SPI_CRC;

#define MAX_HARDWARE_SPI_SPEED 36000//(khz)

void spi_hard_init_fill(SPI_enum, SPI_MasterSlave_mode, int speed, SPI_direction, SPI_datasize, SPI_clock_mode, SPI_FB);

typedef struct
{
    SPI_enum spi;
    Pin_enum cs;
    SPI_clock_mode c_mode;
    int speed;
} Hardware_SPI;

Hardware_SPI spi_hard_init(SPI_enum spi, int speed, SPI_clock_mode c_mode);
void spi_hard_start(Hardware_SPI *spi);
void spi_hard_stop(Hardware_SPI *spi);
uint16_t spi_hard_send_byte(Hardware_SPI *spi, uint8_t byte);
uint16_t spi_hard_send_bytes(Hardware_SPI *spi, uint8_t *buffer, int size);
uint16_t spi_hard_receive_byte(Hardware_SPI *spi);
uint16_t spi_hard_receive_bytes(Hardware_SPI *spi, uint8_t *rec_buf, int size);

size_t spi_hard_write_data(Hardware_SPI *spi, uint8_t byte);
size_t spi_hard_write_datas(Hardware_SPI *spi, const uint8_t *buf, size_t size);
size_t spi_hard_fill_datas(Hardware_SPI *spi, uint8_t byte, size_t size);
uint16_t spi_hard_receive_data(Hardware_SPI *spi);
size_t spi_hard_receive_datas(Hardware_SPI *spi, uint8_t *buf, size_t size);

size_t spi_hard_write_data16(Hardware_SPI *spi, uint16_t byte);
size_t spi_hard_write_data16s(Hardware_SPI *spi, const uint16_t *buf, size_t size);
size_t spi_hard_fill_data16s(Hardware_SPI *spi, uint16_t byte, size_t count);
uint16_t spi_hard_receive_data16(Hardware_SPI *spi);
size_t spi_hard_receive_data16s(Hardware_SPI *spi, uint16_t *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif
