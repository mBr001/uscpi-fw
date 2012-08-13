#include <string.h>
#include <util/delay.h>
#include <util/delay_basic.h>

#include "config.h"
#include "iodef.h"
#include "spi.h"
#include "spi_dev.h"


/* number of currently selected SPI device, see spi.h */
static uint8_t SPI_current_dev;

/* ********** */
static void ad974_init(void) {
	PORT_MODIFY(AD974_DDR, AD974_MASK,
			(DDR_OUT(AD974_A0) |
			DDR_OUT(AD974_A1) |
			DDR_IN(AD974_BUSY) |
			DDR_OUT(AD974_CS) |
			DDR_OUT(AD974_WR) |
			DDR_OUT(AD974_RC)));
	PORT_MODIFY(AD974_PORT, AD974_MASK, (AD974_RC | AD974_WR | AD974_CS));
}

void ad974_set_channel(uint8_t channel)
{
	/* set channel number, 10ns */
	PORT_MODIFY(AD974_PORT, (AD974_A0 | AD974_A1), 
			(((channel & 1) * AD974_A0) |
			(((channel>>1) & 1) * AD974_A1)));
	/* write channel, 50 ns */
	PORT_MODIFY(AD974_PORT, AD974_WR, 0);
	_delay_loop_1(1);
	PORT_MODIFY(AD974_PORT, AD974_WR, AD974_WR);
}

static void ad974_transfer(void *recv, void *UNUSED(send), uint8_t count)
{
	if (count != 2)
		return;
	// select
	PORT_MODIFY(AD974_PORT, AD974_CS, 0);
	// start conversion, 10ns
	PORT_MODIFY(AD974_PORT, AD974_RC, 0);
	// wait until conversion complete 4us + few ns to set-up signals
	_delay_us(5);
//	_delay_loop_1(15);
//	loop_until_bit_is_set(AD974_PORT, AD974_BUSY);
	// read data
	PORT_MODIFY(AD974_PORT, AD974_RC, AD974_RC);
	ad974_set_channel(0);
	// wait for acquisition
//	_delay_loop_1(4);
	_delay_us(1.5);
	// read result
	((uint8_t *)recv)[1] = SPI_transfer8b(0);
	((uint8_t *)recv)[0] = SPI_transfer8b(0);
	// deselect
	PORT_MODIFY(AD974_PORT, AD974_CS, AD974_CS);
}

/* *************************** */
static void mcp4922_init(void)
{
	PORT_MODIFY(MCP4922_DDR, MCP4922_MASK, 
			(DDR_OUT(MCP4922_CS) | DDR_OUT(MCP4922_LD)));
	PORT_MODIFY(MCP4922_PORT, MCP4922_MASK, (MCP4922_CS | MCP4922_LD));
}

static void mcp4922_transfer(void *UNUSED(recv), void *send, uint8_t count)
{
	if (count != 2)
		return;
	// select
	PORT_MODIFY(MCP4922_PORT, MCP4922_CS, 0);
	// write high byte, then low byte
	SPI_transfer8b(((uint8_t *)send)[1]);
	SPI_transfer8b(((uint8_t *)send)[0]);
	// load to output
	PORT_MODIFY(MCP4922_PORT, MCP4922_LD, 0);
	_delay_loop_1(1);
	PORT_MODIFY(MCP4922_PORT, MCP4922_LD, MCP4922_LD);
	// deselect 
	PORT_MODIFY(MCP4922_PORT, MCP4922_CS, MCP4922_CS);
}

void SPI_select_dev(uint8_t dev_num)
{
/*	if (dev_num >= (int8_t)ARRAY_SIZE(spi_devs))
		return;*/
/*	if (SPI_current_dev != -1) {
		spi_devs[SPI_current_dev].select(0);
	}*/
	SPI_current_dev = dev_num;
	switch(SPI_current_dev)
	{
		case SPI_DEV_AD974_0:
			SPCR = SPI_CLOCK_1_4 |
				SPI_PHASE_TRAIL |
				SPI_POL_LOW |
				SPI_DORD_MSB |
				SPI_MODE_MASTER |
				SPI_ENABLE;
//			spi_devs[dev_num].select(1);
			break;
		case SPI_DEV_MCP4922_0:
			SPCR = SPI_CLOCK_1_4 |
				SPI_PHASE_LEAD |
				SPI_POL_LOW |
				SPI_DORD_MSB |
				SPI_MODE_MASTER |
				SPI_ENABLE;
//			spi_devs[dev_num].select(1);
			break;
		case SPI_DEV_NONE:
			return;
	}
}

void SPI_init(void) {
#define SPI_PORT PORTB
#define SPI_DDR DDRB
#define SPI_SS _BV(PB4)
#define SPI_MOSI _BV(PB5)
#define SPI_MISO _BV(PB6)
#define SPI_SCK _BV(PB7)
#define SPI_MASK (SPI_MISO | SPI_SCK | SPI_MOSI | SPI_SS)
	SPI_current_dev = SPI_DEV_NONE;
	SPCR |= SPI_ENABLE;
	SPSR &= ~SPI2X;
	PORT_MODIFY(SPI_DDR, SPI_MASK, 
			(DDR_OUT(SPI_SS | SPI_MOSI | SPI_SCK) | 
			 DDR_IN(SPI_MISO)));
	// set pull-up on input
//	PORT_MODIFY(SPI_PORT, SPI_MISO, SPI_MISO);
	PORT_MODIFY(SPI_PORT, SPI_MISO, 0);
	ad974_init();
	mcp4922_init();
}

uint8_t SPI_transfer8b(uint8_t out) {
	SPDR = out;
//	loop_until_bit_is_set(SPSR, SPIF);
	_delay_loop_1(255);
	return SPDR;
}

void SPI_transfer(void *recv, void *send, uint8_t count)
{
	switch(SPI_current_dev) {
		case SPI_DEV_AD974_0:
			ad974_transfer(recv, send, count);
			break;
		case SPI_DEV_MCP4922_0:
			mcp4922_transfer(recv, send, count);
			break;
	}
}

