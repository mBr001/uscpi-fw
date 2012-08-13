#ifndef __SCPI__
#define __SCPI__

#include "config.h"

#include <stdint.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>

/*
 * SCPI_parse_cont - continue recieving, need more data
 * SCPI_parse_flush - flush buffer - data processed, continue recieving
 * SCPI_parse_flush_last - drop last char from buffer, continue recieving
 * SCPI_parse_end - end of command, call SPIC_parser_reset to start revieving
 * SCPI_parse_err - stop recieving, drop all until newline
 * */
typedef enum SCPI_parse_enum {
	SCPI_parse_cont = 0,
	SCPI_parse_flush = 1,
	SCPI_parse_flush_last = 2,
	SCPI_parse_end = 3,
	SCPI_parse_err = 4
} SCPI_parse_t;

typedef struct SCPI_err_struct {
	const char *str_P;
	uint8_t SES_P;
} SCPI_err_t;

#define SCPI_isstart(c) ( c == ':' || c == '*' || isalpha(c))
void SCPI_err_set(const SCPI_err_t *e);
SCPI_parse_t SCPI_parse(char c);
void SCPI_parser_reset(void);

static const SCPI_err_t SCPI_err_0; 
static const SCPI_err_t SCPI_err_100;
static const SCPI_err_t SCPI_err_102;
static const SCPI_err_t SCPI_err_103;
static const SCPI_err_t SCPI_err_104;
static const SCPI_err_t SCPI_err_108;
static const SCPI_err_t SCPI_err_109;
static const SCPI_err_t SCPI_err_110;
static const SCPI_err_t SCPI_err_112;
static const SCPI_err_t SCPI_err_113;
static const SCPI_err_t SCPI_err_114;
static const SCPI_err_t SCPI_err_171;
static const SCPI_err_t SCPI_err_220;
static const SCPI_err_t SCPI_err_222;
static const SCPI_err_t SCPI_err_223;
static const SCPI_err_t SCPI_err_321;
static const SCPI_err_t SCPI_err_361;
static const SCPI_err_t SCPI_err_362;
static const SCPI_err_t SCPI_err_363;

static const char SCPI_version_P[] PROGMEM = "1999.0";

#endif

/* :set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab */