/*
 * cape.h
 *
 *  Created on: 2016年11月16日
 *      Author: Frank
 */

#ifndef CAPE_H_
#define CAPE_H_

#include "i2c.h"
#include <unistd.h>

#define ReadMode   0
#define WriteMode  1
#define DeAddr    0X4B
#define ConfigValid  0x3a6fb67c

//# TB_WORKMODE

#define TB_SHORT_BREAK   0

#define TB_CW            1
#define TB_CCW           2
//#define TB_STOP          3
//extern unsigned char TB_STOP = '3';
#define TB_WORKMODE_NUM  4


//# TB_PORTMODE

//#define TB_DCM           0
//extern unsigned char TB_DCM = '0';
#define TB_SPM           1
#define TB_PORTMODE_NUM  2


//# SVM_PORT

#define SVM1             0
#define SVM2             1
#define SVM3             2
#define SVM4             3
#define SVM5             4
#define SVM6             5
#define SVM_PORT_NUM     6

// SVM_STATE

#define SVM_DISABLE      0
#define SVM_ENABLE       1
#define SVM_STATE_NUM    2

// IO_MODE

#define IO_IN            0
#define IO_OUT           1
#define IO_MODE_NUM      2

// IO_PUPD

#define IO_PU            0
#define IO_PD            1
#define IO_NP            2
#define IO_PUPD_NUM      3

// IO_PPOD

#define IO_PP            0
#define IO_OD            1
#define IO_PPOD_NUM      2

// IO_STATE

#define IO_LOW           0
#define IO_HIGH          1
#define IO_STATE_NUM     2

// IO_PORT

#define IO1              0
#define IO2              1
#define IO3              2
#define IO4              3
#define IO5              4
#define IO6              5
#define IO_NUM           6


// PARAM_REG

#define CONFIG_VALID         0
//#define CONFIG_TB_PWM_FREQ   CONFIG_VALID + 4
//extern unsigned char CONFIG_TB_PWM_FREQ='4';

#define I2C_ADDRESS          CONFIG_TB_PWM_FREQ + 4

//#define TB_1A_MODE           I2C_ADDRESS + 1
//extern unsigned char TB_1A_MODE = '9';
//#define TB_1A_DIR            TB_1A_MODE + 1
//extern unsigned char TB_1A_DIR = '10';
//#define TB_1A_DUTY           TB_1A_DIR + 1
//extern unsigned char TB_1A_DUTY = '11';
#define TB_1A_SPM_SPEED      TB_1A_DUTY + 2//13
#define TB_1A_SPM_STEP       TB_1A_SPM_SPEED + 4//17

//#define TB_1B_MODE           TB_1A_SPM_STEP + 4//21
//extern unsigned char TB_1B_MODE = '21';
//#define TB_1B_DIR            TB_1B_MODE + 1//22
//extern unsigned char TB_1B_DIR = '22';
//#define TB_1B_DUTY           TB_1B_DIR + 1//23
//extern unsigned char TB_1B_DUTY = '22';
#define TB_1B_SPM_SPEED      TB_1B_DUTY + 2//25
#define TB_1B_SPM_STEP       TB_1B_SPM_SPEED + 4//29

//#define TB_2A_MODE           TB_1B_SPM_STEP + 4//33
//extern unsigned char TB_2A_MODE = '33';
//#define TB_2A_DIR            TB_2A_MODE + 1//34
//extern unsigned char TB_2A_DIR = '34';
//#define TB_2A_DUTY           TB_2A_DIR + 1//35
//extern unsigned char TB_2A_DUTY = '35';
#define TB_2A_SPM_SPEED      TB_2A_DUTY + 2//37
#define TB_2A_SPM_STEP       TB_2A_SPM_SPEED + 4//41

//#define TB_2B_MODE           TB_2A_SPM_STEP + 4//45
//extern unsigned char TB_2B_MODE = '45';
//#define TB_2B_DIR            TB_2B_MODE + 1//46
//extern unsigned char TB_2B_DIR = '46';
//#define TB_2B_DUTY           TB_2B_DIR + 1//47
//extern unsigned char TB_2B_DUTY = '47';
#define TB_2B_SPM_SPEED      TB_2B_DUTY + 2//49
#define TB_2B_SPM_STEP       TB_2B_SPM_SPEED + 4//53

#define SVM1_STATE           TB_2B_SPM_STEP + 4
#define SVM1_FREQ            SVM1_STATE + 1
#define SVM1_ANGLE           SVM1_FREQ + 2

#define SVM2_STATE           SVM1_ANGLE + 2
#define SVM2_FREQ            SVM2_STATE + 1
#define SVM2_ANGLE           SVM2_FREQ + 2

#define SVM3_STATE           SVM2_ANGLE + 2
#define SVM3_FREQ            SVM3_STATE + 1
#define SVM3_ANGLE           SVM3_FREQ + 2

#define SVM4_STATE           SVM3_ANGLE + 2
#define SVM4_FREQ            SVM4_STATE + 1
#define SVM4_ANGLE           SVM4_FREQ + 2

#define SVM5_STATE           SVM4_ANGLE + 2
#define SVM5_FREQ            SVM5_STATE + 1
#define SVM5_ANGLE           SVM5_FREQ + 2

#define SVM6_STATE           SVM5_ANGLE + 2
#define SVM6_FREQ            SVM6_STATE + 1
#define SVM6_ANGLE           SVM6_FREQ + 2

#define IO1_STATE            SVM6_ANGLE + 2
#define IO1_MODE             IO1_STATE + 1
#define IO1_PUPD             IO1_MODE + 1
#define IO1_PPOD             IO1_PUPD + 1

#define IO2_STATE            IO1_PPOD + 1
#define IO2_MODE             IO2_STATE + 1
#define IO2_PUPD             IO2_MODE + 1
#define IO2_PPOD             IO2_PUPD + 1

#define IO3_STATE            IO2_PPOD + 1
#define IO3_MODE             IO3_STATE + 1
#define IO3_PUPD             IO3_MODE + 1
#define IO3_PPOD             IO3_PUPD + 1

#define IO4_STATE            IO3_PPOD + 1
#define IO4_MODE             IO4_STATE + 1
#define IO4_PUPD             IO4_MODE + 1
#define IO4_PPOD             IO4_PUPD + 1

#define IO5_STATE            IO4_PPOD + 1
#define IO5_MODE             IO5_STATE + 1
#define IO5_PUPD             IO5_MODE + 1
#define IO5_PPOD             IO5_PUPD + 1

#define IO6_STATE            IO5_PPOD + 1
#define IO6_MODE             IO6_STATE + 1
#define IO6_PUPD             IO6_MODE + 1
#define IO6_PPOD             IO6_PUPD + 1

#define PARAM_REG_NUM = IO6_PPOD + 1


void WriteByte(unsigned char Reg,unsigned char Value);

void WriteOneWord(unsigned char Reg,unsigned char Value);

class myCape {


	public:

	void DCMotorInit(int MotorName, short Frequency);


	void DCMotorMove(int MotorName,unsigned char Direction, short PWMDuty);


	void DCMotorStop(int MotorName);


};

#endif /* CAPE_H_ */
