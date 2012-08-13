#ifndef __SCPI_IC_H__
#define __SCPI_IC_H__

#include "scpi.h"
#include "ic_sour_temp.h"

extern uint8_t SCPI_params_count;

/* SCPI Instrument Commands */
SCPI_parse_t SCPI_IC_stat_oper_cond(void);
SCPI_parse_t SCPI_IC_stat_oper_enab(void);
SCPI_parse_t SCPI_IC_stat_oper_even(void);
SCPI_parse_t SCPI_IC_stat_pres(void);
SCPI_parse_t SCPI_IC_stat_ques_cond(void);
SCPI_parse_t SCPI_IC_stat_ques_enab(void);
SCPI_parse_t SCPI_IC_stat_ques_even(void);
SCPI_parse_t SCPI_IC_syst_err_next(void);
SCPI_parse_t SCPI_IC_syst_vers(void);

#ifdef SCPI_TEST
SCPI_parse_t SCPI_IC_test_adc(void);
SCPI_parse_t SCPI_IC_test_div(void);
SCPI_parse_t SCPI_IC_test_mul(void);
SCPI_parse_t SCPI_IC_test_num(void);
SCPI_parse_t SCPI_IC_test_temp(void);
SCPI_parse_t SCPI_IC_test_temp_res(void);
SCPI_parse_t SCPI_IC_test_time(void);
SCPI_parse_t SCPI_IC_test_heat(void);
#endif

#endif
/* :set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab */