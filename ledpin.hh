#pragma once

#include "color.hh"
#include "ledseries.hh"
#include "slice/slice.hh"

namespace FastRGB {

/** Stores a Slice of Colors to write to a digital pin */
class LEDPin {
	private:
		/** Stores the colors in this ledpin */
		Slice<Color> leds;
		
		/** What pin to output on */
		unsigned pin;
		
	public:
		/** Constructor to initialize the pin */
		LEDPin(Slice<Color> leds, unsigned pin);
		// No destructor needed as this class is memory safe
		
		void writeByte(unsigned char byte) const;
		
		/** Writes the LED data on the specified digital pin */
		bool display() const;
};

} // end namespace FastRGB