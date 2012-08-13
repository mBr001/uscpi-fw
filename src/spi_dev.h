#ifndef __SPI_DEV_H__
#define __SPI_DEV_H__

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <inttypes.h>

#define SPI_CLOCK (3<<SPR0)
#define SPI_CLOCK_1_4 (0<<SPR0)
#define SPI_CLOCK_1_16 (1<<SPR0)
#define SPI_CLOCK_1_64 (2<<SPR0)
#define SPI_CLOCK_1_128 (3<<SPR0)

#define SPI_PHASE (1<<CPHA)
#define SPI_PHASE_LEAD (0<<CPHA)
#define SPI_PHASE_TRAIL (1<<CPHA)

#define SPI_POL (1<<CPOL)
#define SPI_POL_LOW (0<<CPOL)
#define SPI_POL_HIGH (1<<CPOL)

#define SPI_DORD (1<<DORD)
#define SPI_DORD_LSB (1<<DORD)
#define SPI_DORD_MSB (0<<DORD)

#define SPI_MODE (1<<MSTR)
#define SPI_MODE_SLAVE (0<<MSTR)
#define SPI_MODE_MASTER (1<<MSTR)

#define SPI_ENABLE (1<<SPE)

typedef struct SPI_dev {
	uint8_t mode;
//	uint8_t clock_2x;
//	void (*select)(int enable);
	void (*transfer)(void *recv, void *send, int count);
} SPI_dev_t;

uint8_t SPI_transfer8b(uint8_t out);

#endif
