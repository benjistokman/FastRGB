#pragma once

#include "color.hh"
#include "slice/slice.hh"

namespace FastRGB {

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
bool write(unsigned char * bytes, unsigned bytesLength) {
	cli();
	for (unsigned i = 0; i < bytesLength; i ++) {
		writeByte<pin>(bytes[i]);
	}
	// Delay to help ensure that the led strip will reset its state for reading
	// next message
	delayMicroseconds(20);
	sei();
}

bool writeMultiplex(unsigned char * bytes, unsigned bytesLength, unsigned pin) {
	switch (pin) {
		case 1: write<1>(bytes, bytesLength);
		case 2: write<2>(bytes, bytesLength);
		case 3: write<3>(bytes, bytesLength);
		case 4: write<4>(bytes, bytesLength);
		case 5: write<5>(bytes, bytesLength);
		case 6: write<6>(bytes, bytesLength);
		case 7: write<7>(bytes, bytesLength);
		case 8: write<8>(bytes, bytesLength);
		case 9: write<9>(bytes, bytesLength);
		case 10: write<10>(bytes, bytesLength);
		case 11: write<11>(bytes, bytesLength);
		case 12: write<12>(bytes, bytesLength);
		case 13: write<13>(bytes, bytesLength);
	}
}

} // end namespace FastRGB