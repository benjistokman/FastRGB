#pragma once

#include "color.hh"
#include "slice/slice.hh"

namespace FastRGB {
	
template <unsigned pin> inline void setBit() {}
template <unsigned pin> inline void unsetBit() {}

template <> inline void setBit<0>() {PORTD |= 1;}
template <> inline void unsetBit<0>() {PORTD &= ~1;}
template <> inline void setBit<1>() {PORTD |= 2;}
template <> inline void unsetBit<1>() {PORTD &= ~2;}
template <> inline void setBit<2>() {PORTD |= 4;}
template <> inline void unsetBit<2>() {PORTD &= ~4;}
template <> inline void setBit<3>() {PORTD |= 8;}
template <> inline void unsetBit<3>() {PORTD &= ~8;}
template <> inline void setBit<4>() {PORTD |= 16;}
template <> inline void unsetBit<4>() {PORTD &= ~16;}
template <> inline void setBit<5>() {PORTD |= 32;}
template <> inline void unsetBit<5>() {PORTD &= ~32;}
template <> inline void setBit<6>() {PORTD |= 64;}
template <> inline void unsetBit<6>() {PORTD &= ~64;}
template <> inline void setBit<7>() {PORTD |= 128;}
template <> inline void unsetBit<7>() {PORTD &= ~128;}

template <> inline void setBit<8>() {PORTB |= 1;}
template <> inline void unsetBit<8>() {PORTB &= ~1;}
template <> inline void setBit<9>() {PORTB |= 2;}
template <> inline void unsetBit<9>() {PORTB &= ~2;}
template <> inline void setBit<10>() {PORTB |= 4;}
template <> inline void unsetBit<10>() {PORTB &= ~4;}
template <> inline void setBit<11>() {PORTB |= 8;}
template <> inline void unsetBit<11>() {PORTB &= ~8;}
template <> inline void setBit<12>() {PORTB |= 16;}
template <> inline void unsetBit<12>() {PORTB &= ~16;}
template <> inline void setBit<13>() {PORTB |= 32;}
template <> inline void unsetBit<13>() {PORTB &= ~32;}

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
bool write(Slice<Color> leds) {
	cli();
	// Per color
	for (unsigned i = 0; i < leds.length(); i ++) {
		writeByte<pin>(leds[i].green);
		writeByte<pin>(leds[i].red);
		writeByte<pin>(leds[i].blue);
	}
	delayMicroseconds(50);
	sei();
}

bool writeMultiplex(Slice<Color> leds, unsigned pin) {
	switch (pin) {
		case 1: write<1>(leds);
		case 2: write<2>(leds);
		case 3: write<3>(leds);
		case 4: write<4>(leds);
		case 5: write<5>(leds);
		case 6: write<6>(leds);
		case 7: write<7>(leds);
		case 8: write<8>(leds);
		case 9: write<9>(leds);
		case 10: write<10>(leds);
		case 11: write<11>(leds);
		case 12: write<12>(leds);
		case 13: write<13>(leds);
	}
}

} // end namespace FastRGB