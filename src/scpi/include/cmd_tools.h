#ifndef __SCPI_CMD_TOOLS_H__
#define __SCPI_CMD_TOOLS_H__

#include "scpi.h"

/* used to identify type of parameter */
#define SCPI_PARAMS_MAX 16
extern uint8_t SCPI_params_count;
extern uint8_t SCPI_param_in_buf_idx;

/* SCPI Tools */
SCPI_parse_t SCPI_in_uint8(uint8_t *x);
SCPI_parse_t SCPI_in_uint16(uint16_t *x);
SCPI_parse_t SCPI_in_uint32(uint32_t *x);
SCPI_parse_t SCPI_cmd_err_108(void);

#endif

/* :set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab */