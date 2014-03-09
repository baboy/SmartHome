#include "../device.h"

class Light:public Device{
	public :
		Light();
		void on();
		void off();
		void blink();
		static const char* usage();

	private:
		int io_pin;
};
