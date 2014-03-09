#ifndef _device_h
#define _device_h
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Device{
	public:
	Device();
	void init(); 
	void on();
	void off();
	void output(int pin, int level);
	void outputHigh(int pin);
	void outputLow(int pin);
	
	private:
	int io_pin;
};

#endif
