#include "device.h"

int main(int argc, char *argv[]){
	if(argc <2 ){
		printf("Usage: CMD pin on/off\n");
		return -1;
	}
	int pin = atoi(argv[1]);
	char* st = argv[2];
	int level = LOW;
	if( strcmp(st, "on") == 0){
		level = HIGH;
	}
	printf("IO:%d %d\n", pin, level);
	Device device = Device();
	device.output(pin, level);

}
