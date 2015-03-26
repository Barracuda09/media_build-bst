/*
    SIT2  - DVB-T2/T/C demodulator and tuner

    Copyright (C) 2013 Max Nibble <nibble.max@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef SIT2_H
#define SIT2_H

#include <linux/kconfig.h>
#include <linux/dvb/frontend.h>

struct sit2_config {
	u8 ts_bus_mode; /*1-serial, 2-parallel.*/
	u8 ts_clock_mode; /*0-auto, 1-manual.*/
	
	int (*start_ctrl)(struct dvb_frontend *fe);
};

#if IS_ENABLED(CONFIG_DVB_SIT2)
extern struct dvb_frontend *sit2_attach(const struct sit2_config *config,
					    struct i2c_adapter *i2c);
#else
static inline struct dvb_frontend *sit2_attach(const struct sit2_config *config,
					    struct i2c_adapter *i2c)
{
	printk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}
#endif /* CONFIG_DVB_SIT2 */

#endif /* SIT2_H */
