#include "ledpin.hh"
#include "write.hh"
#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(unsigned pin, unsigned numSections) {
	this->pin = pin;
	this->sections = Slice<Slice<Color>>(numSections);
}

bool LEDPin::set(unsigned sectionNum, Slice<Color> slice) {
	if (sectionNum >= this->sections.length()) {return false;}
	this->sections[sectionNum] = slice;
	return true;
}

bool LEDPin::display() {
	noInterrupts();
	
	pinMode(this->pin, OUTPUT);
	
	unsigned bytesLength = 0;
	for (int i = 0; i < this->sections.length(); i ++) {
		bytesLength += this->sections[i].length();
	}
	bytesLength *= 3;
	
	unsigned char * bytes = new unsigned char[bytesLength];
	unsigned bytesIndex = 0;
	for (int i = 0; i < this->sections.length(); i ++) {
		for (unsigned j = 0; j < this->sections[i].length(); j ++) {
			bytes[bytesIndex] = (unsigned char)(
				float(this->sections[i][j].green)
				* float(this->adjustmentG)
				/ 255.0f
			);
			bytes[bytesIndex+1] = (unsigned char)(
				float(this->sections[i][j].red)
				* float(this->adjustmentR)
				/ 255.0f
			);
			bytes[bytesIndex+2] = (unsigned char)(
				float(this->sections[i][j].blue)
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