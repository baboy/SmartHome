#include "../device.h"

class Fire : public Device{
	public:
		Fire();
		void on();
		void off();
	
	private:
		io_pin;
}
