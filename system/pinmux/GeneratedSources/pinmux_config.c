/*
 **
 ** Source file generated on Agosto 17, 2019 at 19:56:03.	
 **
 ** Copyright (C) 2011-2019 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** I2C0 (SCL0, SDA0)
 ** RTC (RTC_SS1)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** P0_04, P0_05, P2_11
 */

#include <sys/platform.h>
#include <stdint.h>

#define I2C0_SCL0_PORTP0_MUX  ((uint16_t) ((uint16_t) 1<<8))
#define I2C0_SDA0_PORTP0_MUX  ((uint16_t) ((uint16_t) 1<<10))
#define RTC_RTC_SS1_PORTP2_MUX  ((uint32_t) ((uint32_t) 3<<22))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *((volatile uint32_t *)REG_GPIO0_CFG) = I2C0_SCL0_PORTP0_MUX | I2C0_SDA0_PORTP0_MUX;
    *((volatile uint32_t *)REG_GPIO2_CFG) = RTC_RTC_SS1_PORTP2_MUX;

    return 0;
}

