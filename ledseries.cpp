#include "ledseries.hh"

namespace FastRGB {

LEDSeries::LEDSeries(unsigned numLEDs) {
	this->leds = Slice<Color>(numLEDs);
	for (unsigned i = 0; i < this->leds.length(); i ++) {
		this->leds[i].green = 0;
		this->leds[i].red = 0;
		this->leds[i].blue = 0;
	}
}

Slice<Color> LEDSeries::getLEDs(unsigned start, unsigned length) const {
	return this->leds.slice(start, length);
}

Slice<Color> LEDSeries::getLEDs() const {return this->leds;}

bool LEDSeries::updateLED(Color newColor, unsigned index) {
	if (index >= this->getNumLEDs()) {return false;}
	this->leds[index] = newColor;
	return true;
}

bool LEDSeries::update(const Slice<Color> & newLEDs) {
	if (this->getNumLEDs() != newLEDs.length()) {return false;}
	
	for (unsigned i = 0; i < this->getNumLEDs(); i ++) {
		this->leds[i] = newLEDs[i];
	}
	
	return true;
}

} // end namespace FastRGB