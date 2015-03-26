/*+++ *******************************************************************\ 
*     SIT2  - DVB-T2/T/C demodulator and tuner
*
*     --------------------------------------------------------------- 
*     This software is provided "AS IS" without warranty of any kind, 
*     either expressed or implied, including but not limited to the 
*     implied warranties of noninfringement, merchantability and/or 
*     fitness for a particular purpose.
*     --------------------------------------------------------------- 
*   
*     Copyright (c) 2013 ShenZhen Bestunar Ltd,Inc.
*     All rights reserved. 
*     Max Nibble <nibble.max@gmail.com>
*
*
\******************************************************************* ---*/ 

#ifndef SIT2_OP_H
#define SIT2_OP_H

/*structure definition */
typedef struct {
	u8 tunint;
	u8 atvint;
	u8 dtvint;
	u8 err;
	u8 cts;
}sit2_tuner_reply;
 
typedef struct {
	u8 ddint;
	u8 scanint;
	u8 err;
	u8 cts;
}sit2_demod_reply;;

/*global state*/
struct sit2_state {
	struct i2c_adapter *i2c;

	bool  isInited;
	u8 demod_addr;
	u8 tuner_addr;
	u8 sndBuffer[64];
	u8 revBuffer[64];
	sit2_tuner_reply tuner_reply;
	sit2_demod_reply demod_reply;

	fe_delivery_system_t current_system;
	int plp_id;
	u32 stream;
	u32 dvbc_symrate;
	u8 dvbt2_profile;

	u8 ts_bus_mode; /*1-serial, 2-parallel.*/
	u8 ts_clock_mode; /*0-auto, 1-manual.*/
};

struct sit2_mod_state {
	struct dvb_frontend frontend;
	const struct sit2_config *config;
	struct sit2_state drv_state;
};

int sit2_drv_init(struct sit2_state *state);
int sit2_drv_sleep(struct sit2_state *state);

int sit2_drv_set_frontend(struct sit2_state *state,
fe_delivery_system_t delivery_system, u32 frequency, u32 bandwidth_hz,
u32 symbol_rate, fe_modulation_t modulation, u32 stream_id);

int sit2_drv_get_frontend(struct sit2_state *state,
u32 *symbol_rate, fe_modulation_t *modulation, fe_transmit_mode_t *transmission_mode,
fe_guard_interval_t *guard_interval, fe_hierarchy_t *hierarchy, fe_code_rate_t *code_rate_HP,
fe_code_rate_t *code_rate_LP, fe_spectral_inversion_t *inversion, fe_code_rate_t *fec_inner);

int sit2_drv_read_status(struct sit2_state *state, fe_status_t *status);			
int sit2_drv_read_snr(struct sit2_state *state, u16 *snr);
int sit2_drv_read_ber(struct sit2_state *state, u32 *ber);
int sit2_drv_read_ucblocks(struct sit2_state *state, u32 *ucblocks);
int sit2_drv_read_signal_strength(struct sit2_state *state, u16 *strength);
void sit2_op_attach(struct sit2_state *state, struct i2c_adapter *i2c, u8 ts_bus_mode, u8 ts_clock_mode);

#endif /* SIT2_OP_H */
