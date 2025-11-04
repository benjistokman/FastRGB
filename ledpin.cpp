#include "ledpin.hh"
#include "write.hh"
#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(unsigned pin) {
	this->pin = pin;
	this->leds.reserve(1);
}

void LEDPin::add(Slice<Color> newSlice) {this->leds.push_back(newSlice);}

bool LEDPin::display() {
	noInterrupts();
	pinMode(this->pin, OUTPUT);
	
	unsigned bytesLength = 0;
	for (Slice<Color> colorSlice : this->leds) {
		bytesLength += colorSlice.length();
	}
	bytesLength *= 3;
	
	unsigned char * bytes = new unsigned char[bytesLength];
	unsigned bytesIndex = 0;
	for (int i = 0; i < this->leds.size(); i ++) {
		for (unsigned j = 0; j < this->leds[i].length(); j ++) {
			bytes[bytesIndex] = (unsigned char)(
				float(this->leds[i][j].green)
				* float(this->adjustmentG)
				/ 255.0f
			);
			bytes[bytesIndex+1] = (unsigned char)(
				float(this->leds[i][j].red)
				* float(this->adjustmentR)
				/ 255.0f
			);
			bytes[bytesIndex+2] = (unsigned char)(
				float(this->leds[i][j].blue)
				* float(this->adjustmentB)
				/ 255.0f
			);
			bytesIndex += 3;
		}
	}
	
	write(bytes, bytesLength, this->pin);
	
	delete[] bytes;
	interrupts();
}


} // end namespace FastRGB