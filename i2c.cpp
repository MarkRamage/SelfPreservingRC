/*
 * i2c.cpp
 *
 *  Created on: 2016年11月16日
 *      Author: Frank
 */

#include "i2c.h"
#include <iostream>

using namespace std;

myI2C::myI2C(){
	this->i2cOpen();
}

myI2C::~myI2C(){
	this->i2cClose();
}

// open the Linux device
void myI2C::i2cOpen()
{

	i2cFile = open("/dev/i2c-1", O_RDWR);
	if (i2cFile < 0) {
		perror("i2cOpen in myI2C::i2cOpen");
		exit(1);
	}

}

// close the Linux device
void myI2C::i2cClose()
{
	close(i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void myI2C::i2cSetAddress(unsigned char address)
{

	if (ioctl(i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress error in myI2C::i2cSetAddress");
		exit(1);

	}

}


void myI2C::WriteByte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data){
	//i2cSetAddress(DEVICE_ADDR);

	Write_Buf[0] = Reg_ADDR;
	Write_Buf[1] = Data;

	if(write(i2cFile, Write_Buf, 2) != 2) {
		perror("Write Error in myI2C::WriteByte");

	}else{
		perror("WriteByte success");
	}


}

void myI2C::WriteWord(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, short Data){

		//i2cSetAddress(DEVICE_ADDR);

		unsigned char Char1; // lower byte
		unsigned char Char2; // upper byte
		// Split short into two char
		Char1 = Data & 0xFF;
		Char2 = Data >> 8;
		Write_Buf[0] = Reg_ADDR;
		Write_Buf[1] = Char1;//lower byte
		Write_Buf[2] = Char2;//upper byte

		ssize_t s = write(i2cFile, Write_Buf, 3);
		//i2c_smbus_write_word_data(i2cFile, Reg_ADDR, Data);
		if( s != 3) {
			cout << "Wanted to write 3 bytes, but instead wrote " << s << ". " <<endl;
			perror("Write Error in myI2C::Read_Multi_Byte");

		}else{
			perror("WriteWord success");
		}
		/* Using I2C Write, equivalent of
	      i2c_smbus_write_word_data(i2cfile, reg_ADDR, Data)
		  buf[0] = reg;
		  buf[1] = 0x43;
		  buf[2] = 0x65;
		  if (write(file, buf, 3) != 3) {
		  ERROR HANDLING: i2c transaction failed */



}



/*
unsigned char myI2C::ReadByte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR){
	Write_Buf[0] = Reg_ADDR;

	i2cSetAddress(DEVICE_ADDR);
	if(write(i2cFile, Write_Buf, 1) != 1) {
		perror("Write Error in myI2C::Read_I2C_Byte");
	}
	i2cSetAddress(DEVICE_ADDR);
	if(read(i2cFile, Read_Buf, 1) !=1){
		perror("Read Error myI2C::Read_I2C_Byte");
	}

	return Read_Buf[0];
}
*/
/*
unsigned char myI2C::ReadWord(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR){
	Write_Buf[0] = Reg_ADDR;

	i2cSetAddress(DEVICE_ADDR);
	ssize_t s = write(i2cFile, Write_Buf, 1);
	if( s != 1) {
		cout << "Wanted to write " << 1 << " byte, but instead wrote " << s << ". " <<endl;
		perror("Write Error in myI2C::Read_Multi_Byte");
	}
	i2cSetAddress(DEVICE_ADDR);
	ssize_t t = read(i2cFile, Read_Buf, 3);
	if( t != 3)
	{
		cout << "Wanted to read 3 bytes, but instead got " << t << ". " <<endl;
		perror("Read Error in myI2C::Read_Multi_Byte");
	}

	return Read_Buf[0];
}
*/
