#include <ctype.h>
#include <string.h>

#include "lib/extlib.h"
#include "lib/iobuf.h"
#include "cmd.h"
#include "cmd_tools.h"
#include "scpi/error.h"

/* TODO: přemístit sem definici klíče */

SCPI_parse_t SCPI_IC_syst_err_next(void)
{
	const SCPI_err_t *e;

	e = SCPI_err_pop();
	SCPI_print_P((const char*)pgm_read_word(&e->str_P));

        return SCPI_parse_end;
}

SCPI_parse_t SCPI_IC_syst_vers(void)
{
	SCPI_print_P(SCPI_version_P);

        return SCPI_parse_end;
}

/* :set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab */
