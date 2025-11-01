#pragma once

namespace FastRGB {

/// Arduino Uno or Nano
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_NANO328)

template <unsigned pin>
inline void setBit() {
	// Note: the compiler will evaluate these constant expressions at compile
	// time, and will take out all the irrelevant conditional code
	if (pin == 0) {PORTD |= 1;}
	else if (pin == 1) {PORTD |= 2;}
	else if (pin == 2) {PORTD |= 4;}
	else if (pin == 3) {PORTD |= 8;}
	else if (pin == 4) {PORTD |= 16;}
	else if (pin == 5) {PORTD |= 32;}
	else if (pin == 6) {PORTD |= 64;}
	else if (pin == 7) {PORTD |= 128;}
	else if (pin == 8) {PORTB |= 1;}
	else if (pin == 9) {PORTB |= 2;}
	else if (pin == 10) {PORTB |= 4;}
	else if (pin == 11) {PORTB |= 8;}
	else if (pin == 12) {PORTB |= 16;}
	else if (pin == 13) {PORTB |= 32;}
}

template <unsigned pin>
inline void unsetBit() {
	if (pin == 0) {PORTD &= ~1;}
	else if (pin == 1) {PORTD &= ~2;}
	else if (pin == 2) {PORTD &= ~4;}
	else if (pin == 3) {PORTD &= ~8;}
	else if (pin == 4) {PORTD &= ~16;}
	else if (pin == 5) {PORTD &= ~32;}
	else if (pin == 6) {PORTD &= ~64;}
	else if (pin == 7) {PORTD &= ~128;}
	else if (pin == 8) {PORTB &= ~1;}
	else if (pin == 9) {PORTB &= ~2;}
	else if (pin == 10) {PORTB &= ~4;}
	else if (pin == 11) {PORTB &= ~8;}
	else if (pin == 12) {PORTB &= ~16;}
	else if (pin == 13) {PORTB &= ~32;}
}

template <unsigned pin>
void writeByte(unsigned char byte) {
	for (unsigned char bitMask = 0x80; bitMask > 0; bitMask = (bitMask >> 1) ) {
		if ((byte & bitMask) != 0) {
			setBit<pin>();
			__asm__ __volatile__(
				"nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
			);
			unsetBit<pin>();
			__asm__ __volatile__("nop\n\t");
		}
		
		else {
			setBit<pin>();
			__asm__ __volatile__("nop\n\t");
			unsetBit<pin>();
			__asm__ __volatile__(
				"nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
			);
		}
	}
}

template <unsigned pin>
bool writeTemplated(unsigned char * bytes, unsigned bytesLength) {
	cli();
	for (unsigned i = 0; i < bytesLength; i ++) {
		writeByte<pin>(bytes[i]);
	}
	// Delay to help ensure that the led strip will reset its state for reading
	// next message
	delayMicroseconds(20);
	sei();
}

bool write(unsigned char * bytes, unsigned bytesLength, unsigned pin) {
	switch (pin) {
		case 1: writeTemplated<1>(bytes, bytesLength);
		case 2: writeTemplated<2>(bytes, bytesLength);
		case 3: writeTemplated<3>(bytes, bytesLength);
		case 4: writeTemplated<4>(bytes, bytesLength);
		case 5: writeTemplated<5>(bytes, bytesLength);
		case 6: writeTemplated<6>(bytes, bytesLength);
		case 7: writeTemplated<7>(bytes, bytesLength);
		case 8: writeTemplated<8>(bytes, bytesLength);
		case 9: writeTemplated<9>(bytes, bytesLength);
		case 10: writeTemplated<10>(bytes, bytesLength);
		case 11: writeTemplated<11>(bytes, bytesLength);
		case 12: writeTemplated<12>(bytes, bytesLength);
		case 13: writeTemplated<13>(bytes, bytesLength);
	}
}

#elif defined(ARDUINO_ARCH_RENESAS)
	bool write(unsigned char * bytes, unsigned bytesLength, unsigned pin) {
		uint16_t mask = digitalPinToBitMask(pin);
		uint8_t port = digitalPinToPort(pin);
		volatile uint16_t * portx_p = portOutputRegister(port);
		
		noInterrupts();
		for (unsigned i = 0; i < bytesLength; i ++) {
			for (unsigned char bitMask = 0x80; bitMask > 0; bitMask = (bitMask >> 1)) {
				if ((bytes[i] & bitMask) != 0) {
					*portx_p |= mask;
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t");
					*portx_p &= ~mask;
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
				} else {
					*portx_p |= mask;
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
					*portx_p &= ~mask;
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
					__asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t");
				}
			}
		}
		interrupts();
	}
#endif

} // end namespace FastRGB