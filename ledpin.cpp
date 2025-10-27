#include "ledpin.hh"
#include "write.hh"
#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(Slice<Color> leds, unsigned pin) {
	this->leds = leds;
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

bool LEDPin::display() const {
	unsigned char * bytes = new unsigned char[this->leds.length() * 3];
	
	for (unsigned i = 0; i < this->leds.length(); i ++) {
		bytes[i*3+0] = (unsigned char)(
			float(this->leds[i].green)
			* float(this->adjustmentG)
			/ 255.0f
		);
		bytes[i*3+1] = (unsigned char)(
			float(this->leds[i].red)
			* float(this->adjustmentR)
			/ 255.0f
		);
		bytes[i*3+2] = (unsigned char)(
			float(this->leds[i].blue)
			* float(this->adjustmentB)
			/ 255.0f
		);
	}
	
	writeMultiplex(bytes, this->leds.length() * 3, this->pin);
	
	delete[] bytes;
}


} // end namespace FastRGB