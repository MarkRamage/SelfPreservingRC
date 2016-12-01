
#include "cape.h"
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

void error(const char *msg) {
	perror(msg);
	exit(1);
}

int MotorName = 1;
unsigned char Clockwise = '1';
unsigned char CtrClockwise = '2';
unsigned short pwmDuty = '90';
unsigned short freq = '1000';

/*bool motors[5];
#define ERR motors[4]
#define UP motors[3]
#define DOWN motors[2]
#define LEFT motors[1]
#define RIGHT motors[0]
*/

bool err, up, down, left, right;

pthread_mutex_t motorCtrl = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reverseLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t reverseFlag = PTHREAD_COND_INITIALIZER;

char arr[] = "10000";

static void *control(void *p) {
	for (;;) {

	     int sockfd, newsockfd, portno;
	     socklen_t clilen;
	     char buffer[256];
	     struct sockaddr_in serv_addr, cli_addr;
	     int n;
		
	     /*if (argc < 2) {
	         fprintf(stderr,"ERROR, no port provided\n");
	         exit(1);
	     }*/
	     sockfd = socket(AF_INET, SOCK_STREAM, 0);
	     if (sockfd < 0)
	        error("ERROR opening socket");
	     bzero((char *) &serv_addr, sizeof(serv_addr));
	     portno = atoi(arr);
	     serv_addr.sin_family = AF_INET;
	     serv_addr.sin_addr.s_addr = INADDR_ANY;
	     serv_addr.sin_port = htons(portno);
	     if (bind(sockfd, (struct sockaddr *) &serv_addr,
	              sizeof(serv_addr)) < 0)
	              error("ERROR on binding");
	     listen(sockfd,5);
	     clilen = sizeof(cli_addr);
	     newsockfd = accept(sockfd,
	                 (struct sockaddr *) &cli_addr,
	                 &clilen);
	     if (newsockfd < 0)
	          error("ERROR on accept");
	     bzero(buffer,256);
	     n = read(newsockfd,buffer,2);
	     if (n < 0) error("ERROR reading from socket");
	     pthread_mutex_lock(&motorCtrl);
	     if (buffer[0] == 'u')
	     {
	         up = true;
	         down = false;
	     }
	     if (buffer[0] == 'd')
	     {
	         up = false;
	         down = true;
	     }
	     if (buffer[0] == 'o')
	     {
	         up = false;
	         down = false;
	     }
	     if (buffer[1] == 'l')
	     {
	         left = true;
	         right = false;
	     }
	     if (buffer[1] == 'r')
	     {
	         right = true;
	         left = false;
	     }
	     if (buffer[1] == 'o')
	     {
	         right = false;
	         left = false;
	     }
	     pthread_mutex_unlock(&motorCtrl);
	     printf("Here is the message: %s\n",buffer);
	     n = write(newsockfd,"I got your message",18);

	     if (n < 0) error("ERROR writing to socket");
	     close(newsockfd);
	     close(sockfd);
	     return 0;

	}
}

static void *sensor(void *p) {
	int file, luminance, proximity;
	char *bus = "/dev/i2c-1";
	for (;;) {
		if ((file = open(bus, O_RDWR)) < 0){
			printf("Failed to open the bus. \n");
			exit(1);
		}
		// Get I2C device, VCNL4010 I2C address is 0x13(19)
		ioctl(file, I2C_SLAVE, 0x13);

		// Select command register(0x80)
		// Enables ALS and proximity measurement, LP oscillator(0xFF)
		char config[2] = {0};
		config[0] = 0x80;
		config[1] = 0xFF;
		write(file, config, 2);
		// Select proximity rate register(0x82)
		// 1.95 proximity measurement / s(0x00)
		config[0] = 0x82;
		config[1] = 0x00;
		write(file, config, 2);
		// Select ALS register(0x84)
		// Continuos conversion mode, ALS rate 2 samples / s(0x9D)
		config[0] = 0x84;
		config[1] = 0x9D;
		write(file, config, 2);

		int i = 0;
		int j = 0;
		while(1){
			j = 0;
			for(i = 0;i<50000000;i++){
				j++;
			}
			char reg[1] = {0x85};
			write(file, reg, 1);
			char data[4] ={0};

			if(read(file, data, 4) != 4)
			{
				printf("Error : Input/Output error \n");
			} else {
				// Convert the data
				luminance = (data[0] * 256 + data[1]);
				proximity = (data[2] * 256 + data[3]);

				// Output data to screen
				printf("Ambient Light Luminance : %d lux \n", luminance);
				printf("Proximity Of The Device : %d \n", proximity);
			}
		}
		//get info from client
		pthread_mutex_lock(&motorCtrl);
		if (proximity < ) {
			up = false;
			down = true;
			right = false;
			left = false;
			err = true;
		}
		pthread_mutex_unlock(&motorCtrl);
	}
}

static void *motor(void *p) {

    FILE *LEDhandle=NULL;
    char *LED0brightness = "/sys/devices/ocp.3/gpio-leds.8/leds/beaglebone:green:usr0/brightness";
    char *LED1brightness = "/sys/devices/ocp.3/gpio-leds.8/leds/beaglebone:green:usr1/brightness";
    char *LED2brightness = "/sys/devices/ocp.3/gpio-leds.8/leds/beaglebone:green:usr2/brightness";
    char *LED3brightness = "/sys/devices/ocp.3/gpio-leds.8/leds/beaglebone:green:usr3/brightness";

	for (;;) {

		pthread_mutex_lock(&motorCtrl);
		if((LEDhandle = fopen(LED3brightness,"r+"))!=NULL) {
			if (up) {
				fwrite("1", sizeof(char), 1, LEDhandle);
			} else {
				fwrite("0", sizeof(char), 1, LEDhandle);
			}
			fclose(LEDhandle);
		}
		if ((LEDhandle = fopen(LED2brightness, "r+")) != NULL) {
			if (down) {
				fwrite("1", sizeof(char), 1, LEDhandle);
			} else {
				fwrite("0", sizeof(char), 1, LEDhandle);
			}
			fclose(LEDhandle);
		}
		if ((LEDhandle = fopen(LED1brightness, "r+")) != NULL) {
			if (left) {
				fwrite("1", sizeof(char), 1, LEDhandle);
			} else {
				fwrite("0", sizeof(char), 1, LEDhandle);
			}
			fclose(LEDhandle);
		}
		if ((LEDhandle = fopen(LED0brightness, "r+")) != NULL) {
			if (left) {
				fwrite("1", sizeof(char), 1, LEDhandle);
			} else {
				fwrite("0", sizeof(char), 1, LEDhandle);
			}
			fclose(LEDhandle);
		}


		if (ERR == true) {
			usleep(300000);
		}
		pthread_mutex_unlock(&motorCtrl);

	}
}


int main(int argc, char* argv[]) {
	/*
	myCape *capeptr = new myCape();
	capeptr->DCMotorInit(MotorName, Frequency);
	*/

	pthread_t main_id, control_id, IR_id, motor_id;
	pthread_attr_t myattr;
	int err;
	void *returnvalue;

	main_id = pthread_self();


	pthread_attr_init(&myattr);
	pthread_attr_setinheritsched(&myattr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myattr,SCHED_RR);
	// pthread_attr_setschedparam(&myattr,);

	err = pthread_create(&control_id, &myattr, control, NULL);
	err = pthread_create(&IR_id, &myattr, sensor, NULL);
	err = pthread_create(&motor_id, &myattr, motor, NULL);

	pthread_attr_destroy(&myattr);

	pthread_join(control_id, &returnvalue);
	pthread_join(IR_id, &returnvalue);
	pthread_join(motor_id, &returnvalue);

	return 0;
}




