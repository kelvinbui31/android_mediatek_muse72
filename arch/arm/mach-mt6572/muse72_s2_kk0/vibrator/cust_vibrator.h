#ifndef __CUST_VIBRATOR_H__
#define __CUST_VIBRATOR_H__

#include <mach/mt_reg_base.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>

#define CUST_VIBR_LIMIT
/*----------------------------------------------------------------------------*/
struct vibrator_hw {
	int	vib_timer;
#ifdef CUST_VIBR_LIMIT
	int	vib_limit;
#endif
	MT65XX_POWER_VOLTAGE vosel;
};
/*----------------------------------------------------------------------------*/
extern struct vibrator_hw *get_cust_vibrator_hw(void);
/*----------------------------------------------------------------------------*/
#endif
