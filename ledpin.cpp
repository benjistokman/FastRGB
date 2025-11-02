#include "ledpin.hh"
#include "write.hh"
#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(unsigned pin) {
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

LEDPin::add(Slice<Color> newSlice) {
	this->leds.push_back(newSlice);
}

bool LEDPin::display() const {
	unsigned bytesLength = 0;
	for (Slice<Color> colorSlice : this->leds) {
		bytesLength += colorSlice.length();
	}
	bytesLength *= 3;
	
	unsigned char * bytes = new unsigned char[bytesLength];
	unsigned bytesIndex = 0;
	
	for (Slice<Color> colorSlice : this->leds) {
		for (unsigned i = 0; i < colorSlice.length(); i ++) {
			bytes[bytesIndex] = (unsigned char)(
				float(colorSlice[i].green)
				* float(this->adjustmentG)
				/ 255.0f
			);
			bytes[bytesIndex+1] = (unsigned char)(
				float(colorSlice[i].red)
				* float(this->adjustmentR)
				/ 255.0f
			);
			bytes[bytesIndex+2] = (unsigned char)(
				float(colorSlice[i].blue)
				* float(this->adjustmentB)
				/ 255.0f
			);
			bytesIndex += 3;
		}
	}
	
	write(bytes, bytesLength, this->pin);
	
	delete[] bytes;
}


} // end namespace FastRGB