#include "i2c_sleep.h"
#include <sys/platform.h>
#include <stdio.h>
#include "common.h"
#include "adi_initialize.h"
#include "i2c.h"
#include "pwr.h"
#include "drivers/rtc/adi_rtc.h"

int main(int argc, char *argv[])
{
	//setup
	adi_initComponents();

	//power setup
	ADI_PWR_RESULT pwrr = pwrSetup();
	if(pwrr)
		return pwrr;

	//i2c setup
	ADI_I2C_RESULT i2cr = i2cSetup(400000);
	if(i2cr)
		return i2cr;

	uint8_t data;
	if(i2cRead(0x48, 1, &data))
		return 1;
	DEBUG_MESSAGE("%c", data);
	return 0;
}
