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
		
		/** Adjustment for red channel */
		unsigned char adjustmentR = 255;
		/** Adjustment for green channel */
		unsigned char adjustmentG = 255;
		/** Adjustment for blue channel */
		unsigned char adjustmentB = 255;
		
	public:
		/** Constructor to initialize the pin */
		LEDPin(Slice<Color> leds, unsigned pin);
		// No destructor needed as this class is memory safe
		
		void writeByte(unsigned char byte) const;
		
		/** Writes the LED data on the specified digital pin */
		bool display() const;
		
		
		/** Adjustment for red channel */
		void setAdjustmentR(unsigned char adjustmentR) {
			this->adjustmentR = adjustmentR;
		}
		/** Adjustment for green channel */
		void setAdjustmentG(unsigned char adjustmentG) {
			this->adjustmentG = adjustmentG;
		}
		/** Adjustment for blue channel */
		void setAdjustmentB(unsigned char adjustmentB) {
			this->adjustmentB = adjustmentB;
		}
};

} // end namespace FastRGB