/*
 * cape.cpp
 *
 *  Created on: 2016年11月16日
 *      Author: Frank
 */


#include "cape.h"
//Reset = "P9_23";

//GPIO.setup(Reset, GPIO.OUT)

myI2C *i2cptr = new myI2C();


unsigned char TB_1A_MODE = '9';
unsigned char TB_1A_DIR = '10';
unsigned char TB_1A_DUTY = '11';

unsigned char TB_1B_MODE = '21';
unsigned char TB_1B_DIR = '22';
unsigned char TB_1B_DUTY = '22';


unsigned char TB_2A_MODE = '33';
unsigned char TB_2A_DIR = '34';
unsigned char TB_2A_DUTY = '35';

unsigned char TB_2B_MODE = '45';
unsigned char TB_2B_DIR = '46';
unsigned char TB_2B_DUTY = '47';

unsigned char TB_STOP = '3';
unsigned char TB_DCM = '0';

unsigned char CONFIG_TB_PWM_FREQ='4';


void WriteByte(unsigned char Reg,unsigned char Value){

i2cptr->WriteByte(0x4b,Reg,Value);

//void SendByte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data);
}

void WriteOneWord(unsigned char Reg, short Value){

i2cptr->WriteWord(0x4b,Reg,Value);

//void WriteWord(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data);
}



void myCape::DCMotorInit(int MotorName, short Frequency){

	i2cptr->i2cSetAddress(0x4b);
	WriteOneWord(CONFIG_TB_PWM_FREQ,Frequency);
	usleep(5000);


	    //# Set the port as DC Motor
	        if (MotorName == 1 || MotorName == 2){
	            WriteByte(TB_1A_MODE,TB_DCM);
	            usleep(5000);
	            WriteByte(TB_1A_DIR,TB_STOP);
	            usleep(5000);
	            WriteByte(TB_1B_MODE,TB_DCM);
	            usleep(5000);
	            WriteByte(TB_1B_DIR,TB_STOP);
	            usleep(5000);
	        }
	        if (MotorName == 3 || MotorName == 4){
	            WriteByte(TB_2A_MODE,TB_DCM);
	            usleep(5000);
	            WriteByte(TB_2A_DIR,TB_STOP);
	            usleep(5000);
	            WriteByte(TB_2B_MODE,TB_DCM);
	            usleep(5000);
	            WriteByte(TB_2B_DIR,TB_STOP);
	            usleep(5000);
	        }

}


void myCape::DCMotorMove(int MotorName,unsigned char Direction, short PWMDuty){

			if (MotorName == 1){
	            WriteByte(TB_1B_DIR,Direction);
	            usleep(5000);
	            //WriteOneWord(TB_1B_DUTY,PWMDuty*10);
	            WriteOneWord(TB_1B_DUTY,(short)'900');
	            usleep(5000);
			}

	        if (MotorName == 2){
	            WriteByte(TB_1A_DIR,Direction);
	            usleep(5000);
	            //WriteOneWord(TB_1A_DUTY,PWMDuty*10);
	            WriteOneWord(TB_1A_DUTY,(short)'900');
	            usleep(5000);
	        }

	        if (MotorName == 3){
	            WriteByte(TB_2B_DIR,Direction);
	            usleep(5000);
	            //WriteOneWord(TB_2B_DUTY,PWMDuty*10);
	            WriteOneWord(TB_2B_DUTY,(short)'900');
	            usleep(5000);
	        }

	        if (MotorName == 4){
	            WriteByte(TB_2A_DIR,Direction);
	            usleep(5000);
	            //WriteOneWord(TB_2A_DUTY,PWMDuty*10);
	            WriteOneWord(TB_2A_DUTY,(short)'900');
	            usleep(5000);
	        }

}


void myCape::DCMotorStop(int MotorName){

			if (MotorName == 1){
	            WriteByte(TB_1B_DIR,TB_STOP);
			}
	        if (MotorName == 2){
	            WriteByte(TB_1A_DIR,TB_STOP);
	        }
	        if (MotorName == 3){
	            WriteByte(TB_2B_DIR,TB_STOP);
	        }
	        if (MotorName == 4){
	            WriteByte(TB_2A_DIR,TB_STOP);
	        }
	        usleep(5000);


}



/*
def WriteByte(Reg,Value):
    data = [0 for i in range(2)]
    data[0] = Reg
    data[1] = Value
    MotorBridge.writeList(WriteMode,data)

def WriteHalfWord(Reg,Value):
    data = [0 for i in range(3)]
    data[0] = Reg
    data[1] = Value & 0xff
    data[2] = (Value>>8) & 0xff
    MotorBridge.writeList(WriteMode,data)

def WriteOneWord(Reg,Value):
    data = [0 for i in range(5)]
    data[0] = Reg
    data[1] = Value & 0xff
    data[2] = (Value>>8) & 0xff
    data[3] = (Value>>16) & 0xff
    data[4] = (Value>>24) & 0xff
    MotorBridge.writeList(WriteMode,data)

def SetDefault():
    WriteOneWord(CONFIG_VALID,0x00000000)

class MotorBridgeCape:
    def __init__(self):
        GPIO.output(Reset, GPIO.HIGH)
        time.sleep(1)



    # Init DC Motor
    def DCMotorInit(self,MotorName,Frequency):
    # Init the DC Frequency
        WriteOneWord(CONFIG_TB_PWM_FREQ,Frequency)
        time.sleep(DelayTime)

    # Set the port as DC Motor
        if MotorName == 1 or MotorName == 2:
            WriteByte(TB_1A_MODE,TB_DCM)
            time.sleep(DelayTime)
            WriteByte(TB_1A_DIR,TB_STOP)
            time.sleep(DelayTime)
            WriteByte(TB_1B_MODE,TB_DCM)
            time.sleep(DelayTime)
            WriteByte(TB_1B_DIR,TB_STOP)
            time.sleep(DelayTime)
        if MotorName == 3 or MotorName == 4:
            WriteByte(TB_2A_MODE,TB_DCM)
            time.sleep(DelayTime)
            WriteByte(TB_2A_DIR,TB_STOP)
            time.sleep(DelayTime)
            WriteByte(TB_2B_MODE,TB_DCM)
            time.sleep(DelayTime)
            WriteByte(TB_2B_DIR,TB_STOP)
            time.sleep(DelayTime)

    # Drive the DC Motor
    # Direction 1 CW | 2 CCW
    # PWNDuty  0 ~ 100
    def DCMotorMove(self, MotorName,Direction,PWMDuty):
        if MotorName == 1:
            WriteByte(TB_1B_DIR,Direction)
            time.sleep(DelayTime)
            WriteOneWord(TB_1B_DUTY,PWMDuty*10)
            time.sleep(DelayTime)

        if MotorName == 2:
            WriteByte(TB_1A_DIR,Direction)
            time.sleep(DelayTime)
            WriteOneWord(TB_1A_DUTY,PWMDuty*10)
            time.sleep(DelayTime)

        if MotorName == 3:
            WriteByte(TB_2B_DIR,Direction)
            time.sleep(DelayTime)
            WriteOneWord(TB_2B_DUTY,PWMDuty*10)
            time.sleep(DelayTime)

        if MotorName == 4:
            WriteByte(TB_2A_DIR,Direction)
            time.sleep(DelayTime)
            WriteOneWord(TB_2A_DUTY,PWMDuty*10)
            time.sleep(DelayTime)

    # Stop the DC motor
    def DCMotorStop(self, MotorName):
        if MotorName == 1:
            WriteByte(TB_1B_DIR,TB_STOP)
        if MotorName == 2:
            WriteByte(TB_1A_DIR,TB_STOP)
        if MotorName == 3:
            WriteByte(TB_2B_DIR,TB_STOP)
        if MotorName == 4:
            WriteByte(TB_2A_DIR,TB_STOP)
        time.sleep(DelayTime)



if __name__=="__main__":

    motor = MotorBridgeCape()

*/
