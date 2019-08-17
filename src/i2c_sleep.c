#include "i2c_sleep.h"
#include <sys/platform.h>
#include "adi_initialize.h"
#include "drivers/i2c/adi_i2c.h"
#include "drivers/pwr/adi_pwr.h"
#include "drivers/rtc/adi_rtc.h"

//i2c variables
uint8_t i2c_mem[ADI_I2C_MEMORY_SIZE];
ADI_I2C_HANDLE i2c_device;
uint32_t i2c_hwErrors;

ADI_I2C_RESULT i2cRead(uint16_t const SlaveAddress, uint8_t bytes, uint8_t* data)
{
	ADI_I2C_RESULT result;
	ADI_I2C_TRANSACTION transaction;

	//set slave address
	result = adi_i2c_SetSlaveAddress(i2c_device, SlaveAddress);
	if(result)
		return result;

	//build transaction
	transaction.nDataSize = bytes;
	transaction.pData = data;
	transaction.bReadNotWrite = true;
	transaction.bRepeatStart = true;

	result = adi_i2c_ReadWrite(i2c_device, &transaction, &i2c_hwErrors);
	if(result)
		return result;
	return 0;
}

ADI_I2C_RESULT i2cWrite(uint16_t const SlaveAddress, uint8_t bytes, uint8_t* data)
{
	ADI_I2C_RESULT result;
	ADI_I2C_TRANSACTION transaction;

	//set slave address
	result = adi_i2c_SetSlaveAddress(i2c_device, SlaveAddress);
	if(result)
		return result;

	//build transaction
	transaction.nDataSize = bytes;
	transaction.pData = data;
	transaction.bReadNotWrite = false;
	transaction.bRepeatStart = true;

	result = adi_i2c_ReadWrite(i2c_device, &transaction, &i2c_hwErrors);
	if(result)
		return result;
	return 0;
}

static ADI_PWR_RESULT pwrSetup()
{
  ADI_PWR_RESULT eResult;

  if(ADI_PWR_SUCCESS !=(eResult=adi_pwr_Init()))
  {
    return eResult;
  }

  if(ADI_PWR_SUCCESS !=(eResult=adi_pwr_SetLFClockMux(ADI_CLOCK_MUX_LFCLK_LFXTAL)))
  {
    return eResult;
  }

  if(ADI_PWR_SUCCESS !=(eResult=adi_pwr_EnableClockSource(ADI_CLOCK_SOURCE_LFXTAL,true)))
  {
    return eResult;
  }

  if(ADI_PWR_SUCCESS !=(eResult=adi_pwr_SetClockDivider(ADI_CLOCK_HCLK,1)))
  {
    return eResult;
  }

  if(ADI_PWR_SUCCESS !=(eResult=adi_pwr_SetClockDivider(ADI_CLOCK_PCLK,1)))
  {
    return eResult;
  }

  return(eResult);
}

ADI_I2C_RESULT i2cSetup(uint32_t const requestedBitRate32)
{
	ADI_I2C_RESULT eResult;

	if(ADI_I2C_SUCCESS != (eResult=adi_i2c_Open(0, i2c_mem, ADI_I2C_MEMORY_SIZE, &i2c_device)))
	{
		return eResult;
	}

	if(ADI_I2C_SUCCESS != (eResult=adi_i2c_Reset(i2c_device)))
	{
		return eResult;
	}

	if(ADI_I2C_SUCCESS != (eResult=adi_i2c_SetBitRate(i2c_device, requestedBitRate32)))
	{
		return eResult;
	}

	return eResult;
}

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


	//adi_rtc_Open();

	uint8_t data;
	if(i2cRead(0x48, 1, &data))
		return 1;
	return 0;
}
