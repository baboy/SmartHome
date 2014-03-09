#include "light.h"

Light::Light():Device(){
	this->io_pin = 18;
}
void Light::on(){
	this->outputHigh(this->io_pin);
}
void Light::off(){
	this->outputLow(this->io_pin);
}

void Light::blink(){
	int n = 20;
	while(n-->0){
		this->on();
		delay(800);
		this->off();
		delay(800);
	}
}
const char* Light::usage(){
	const char *s = "Usage: light on/off/blink\n";
	return s;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		printf(Light::usage());
		return -1;
	}
	Light light = Light();
	char *p = argv[1];
	if(strcmp(p, "on") == 0){
		light.on();
	}else if(strcmp(p, "off") == 0){
		light.off();
	}else if (strcmp(p, "blink") == 0){
		light.blink();
	}else {
		printf(Light::usage());
		return -1;
	}
	return 0;
}
