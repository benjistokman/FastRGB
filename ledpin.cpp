#include "ledpin.hh"
#include "write.hh"

#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(Slice<Color> leds, unsigned	 pin) {
	this->leds = leds;
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

bool LEDPin::display() const {
	writeMultiplex(this->leds, this->pin);
}


} // end namespace FastRGB