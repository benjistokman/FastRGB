#pragma once

#include "color.hh"
#include "slice/slice.hh"

#include <ArxSmartPtr.h>

namespace FastRGB {

/** Stores a set of Colors in order */
class LEDSeries {
	private:
		/** Stores the colors in this series
			@WARNING this vector simply provices a memory-safe abstraction on top
					 top of an array of Color objects. Other classes use an
					 std::span on top of it. */
		Slice<Color> leds;
		
	public:
		/** Constructor to initialize the series */
		LEDSeries(unsigned numLEDs);
		
		/** Gets a partial copy of this->leds */
		Slice<Color> getLEDs(unsigned start, unsigned length) const;
		/** Gets a full copy of this->leds */
		Slice<Color> getLEDs() const;
		/** Gets number of LEDs */
		unsigned getNumLEDs() const {return this->leds.length();}
		
		/** Sets an LED color to something specific
			@return ture on success */
		bool updateLED(Color newColor, unsigned index);
		
		/** Updates the LEDs in this object to the */
		bool update(Slice<Color> & newLEDs);
};

} // end namespace FastRGB