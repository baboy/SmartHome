#include "device.h"

Device::Device(){
	this->io_pin = 18;
	this->init();
}
void Device::init(){
	wiringPiSetupGpio();
}
void Device::on(){
	printf("Device:on\n");
}
void Device::off(){
	printf("Device:on\n");
}

void Device::output(int pin, int level){
	pinMode(pin, OUTPUT);
	digitalWrite(pin, level);
}
void Device::outputHigh(int pin){
	this->output(pin, HIGH);
}
void Device::outputLow(int pin){
	this->output(pin, LOW);
}


