#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Turns the colors to black, with an optional fade out */
class EffectOff : public Effect {
	private:
		bool fadeOut = false;
		
	public:
		EffectOff() {}
		EffectOff(bool fadeOut) {this->fadeOut = fadeOut;}
		
		void next(Slice<Color> leds) {
			float multiple = 0;
			if (this->fadeOut) {multiple = 0.95;}
			
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = (unsigned char)((float)leds[i].red*multiple);
				leds[i].green = (unsigned char)((float)leds[i].green*multiple);
				leds[i].blue = (unsigned char)((float)leds[i].blue*multiple);
			}
		}
		
		void tick() {/* Does nothing */}
};

} // end namespace FastRGB