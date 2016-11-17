/*
 * i2c.h
 *
 *  Created on: 2016年11月16日
 *      Author: Frank
 */

#ifndef I2C_H_
#define I2C_H_

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#define MAX_BUFFER_SIZE					64

class myI2C {
	int i2cFile;
public:
	myI2C();
	~myI2C();

	// Public Variables
	unsigned char Write_Buf[MAX_BUFFER_SIZE];			// Contains data you want to send
	unsigned char Read_Buf[MAX_BUFFER_SIZE];			// Contains data which was read

	// Initialize Functions
	void i2cOpen();										// Opens i2cbus 3, done at the beginning
	void i2cClose();									// Closes i2cbus 3, done at the ending
	void i2cSetAddress(unsigned char address);					// Changes device address

	// Sends a single byte <Data> to <DEVICE_ADDR> on the register <Reg_ADDR>
	void WriteByte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data);

	// Reads and returns a single byte from <DEVICE_ADDR> on the register <Reg_ADDR>
	//unsigned char ReadByte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR);

	// Reads multipes byte from <DEVICE_ADDR> starting from the register address <Reg_ADDR>.
	// Read the output from i2cptr->I2C_RD_Buf
	//unsigned char ReadWord(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR);


	void WriteWord(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, short Data);
};


#endif /* I2C_H_ */
