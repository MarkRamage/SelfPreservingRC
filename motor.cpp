/*
 * motor.cpp
 *
 *  Created on: 2016年11月16日
 *      Author: Frank
 */

#include "cape.h"
#include <string.h>


//#define MotorName        1
//#define ClockWise        1
//#define CounterClockWise 2
//#define PwmDuty          90
//#define Frequency        1000


int MotorName = 1;
unsigned char ClockWise = '1';
unsigned char CounterClockWise = '2';
unsigned short PwmDuty = '90';
unsigned short Frequency = '1000';


int main(){

/*
	int GPIOPin=49; // GPIO1_28 or pin 12 on the P9 header

	    printf("\nStarting GPIO output program\n");
	    FILE *myOutputHandle = NULL;
	    char setValue[4], GPIOString[4], GPIOValue[64], GPIODirection[64];
	    sprintf(GPIOString, "%d", GPIOPin);
	    sprintf(GPIOValue, "/sys/class/gpio/gpio%d/value", GPIOPin);
	    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", GPIOPin);

	     //Export the pin
	    if ((myOutputHandle = fopen("/sys/class/gpio/export", "ab")) == NULL){
	        //printf("Unable to export GPIO pin\n");
	        return 1;
	    }
	    strcpy(setValue, GPIOString);
	    fwrite(&setValue, sizeof(char), 2, myOutputHandle);
	    fclose(myOutputHandle);

	     //Set direction of the pin to an output
	    if ((myOutputHandle = fopen(GPIODirection, "rb+")) == NULL){
	        printf("Unable to open direction handle\n");
	        return 1;
	    }
	    strcpy(setValue,"out");
	    fwrite(&setValue, sizeof(char), 3, myOutputHandle);
	    fclose(myOutputHandle);


	        // Set output to high
	        if ((myOutputHandle = fopen(GPIOValue, "rb+")) == NULL){
	            printf("Unable to open value handle\n");
	            return 1;
	        }
	        strcpy(setValue, "1"); // Set value high
	        fwrite(&setValue, sizeof(char), 1, myOutputHandle);
	        fclose(myOutputHandle);
	        sleep(1); // wait for 1 sec

*/

	myCape *capeptr = new myCape();
	capeptr->DCMotorInit(MotorName,Frequency);
	while (1){
	        capeptr->DCMotorMove(MotorName,ClockWise,PwmDuty);
	        printf("motorMove\n");
	        //usleep(5000);
	        sleep(2);
			capeptr->DCMotorMove(MotorName,CounterClockWise,PwmDuty);
			printf("motorMove\n");
			//usleep(5000);
			sleep(2);
			capeptr->DCMotorStop(MotorName);
			printf("motorStop\n");
			//usleep(5000);
			sleep(2);
	}

}

/*
motor = MotorBridge.MotorBridgeCape()
    motor.DCMotorInit(MotorName,Frequency)
    while True:
        motor.DCMotorMove(MotorName,ClockWise,PwmDuty)
        time.sleep(2)
        motor.DCMotorMove(MotorName,CounterClockWise,PwmDuty)
        time.sleep(2)
        print "hello"
        motor.DCMotorStop(MotorName)
        time.sleep(2)
*/
