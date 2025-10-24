#include "ledpin.hh"

#include <Arduino.h>

namespace FastRGB {

LEDPin::LEDPin(Slice<Color> leds, unsigned short pin) {
	this->leds = leds;
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

void LEDPin::writeByte(unsigned char byte) const {
	volatile uint8_t * port = portOutputRegister(digitalPinToPort(pin));
	uint8_t bitMask = digitalPinToBitMask(pin);
	
	for (unsigned char bitMask = 0x80; bitMask > 0; bitMask = (bitMask >> 1) ) {
		if ((byte & bitMask) != 0) {
			// ~0.8us high, ~0.45us low (approx)
			PORTB |= 4;
			__asm__ __volatile__(
			"nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
			);
			PORTB &= ~4;
			__asm__ __volatile__("nop\n\t"); // pad
		} else {
			// ~0.4us high, ~0.85us low (approx)
			PORTB |= 4;
			__asm__ __volatile__("nop\n\t"); // ~4 nops
			PORTB &= ~4;
			__asm__ __volatile__(
			"nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
			);
		}
	}
}

bool LEDPin::display() const {
	cli();
	// Per color
	for (unsigned i = 0; i < this->leds.length(); i ++) {
		this->writeByte(this->leds[i].green);
		this->writeByte(this->leds[i].red);
		this->writeByte(this->leds[i].blue);
	}
	digitalWrite(this->pin, LOW);
	delayMicroseconds(50);
	sei();
}

} // end namespace FastRGB