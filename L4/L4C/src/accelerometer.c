
#include "SPI.h"
#include "SysTimer.h"
#include "accelerometer.h"

void accWrite(uint8_t addr, uint8_t val)
{
	// TODO access SPI_Transfer_Data
	// cmd byte is 1R/W, 1MB, and 6 command bits (the address)
	uint16_t write = 0;
	write = 0 << 15 | 0 << 14 | addr << 8 | val;
	SPI_Transfer_Data(write);
}

uint8_t accRead(uint8_t addr)
{
	// access SPI_Transfer_Data, second byte is empty so MB (multibyte) transfer bit is low
	uint16_t read = 0;

	read = 1 << 15 | 0 << 14 | addr << 8;

	return (uint8_t)SPI_Transfer_Data(read); // TODO
}

void initAcc(void)
{
	accWrite(0x31, 0x08);

	// enable measurement
	accWrite(0x2D, 0x08);
}

void readValues(double *x, double *y, double *z)
{
	// TODO
	// find scaler from data sheet
	// read values into x,y,z using accRead
	*x = (short)(accRead(0x33) << 8 | accRead(0x32)) * 3.9E-3;
	*y = (short)(accRead(0x35) << 8 | accRead(0x34)) * 3.9E-3;
	*z = (short)(accRead(0x37) << 8 | accRead(0x36)) * 3.9E-3;
}