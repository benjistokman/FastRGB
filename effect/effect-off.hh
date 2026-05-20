#pragma once

#include "effect.hh"

namespace FastRGB {

/* Turns the colors to black, with an optional fade out */
class EffectOff : public Effect {
	private:
		float fadeOut = 0;
		
	public:
		/* Will write black to all Colors */
		EffectOff() {}
		/* Will write black to all Colors */
		EffectOff(
			/* The number to multiply each Color by, reccomend 0.9 or so, set to
			   0 to turn of instantly. */
			float fadeOut
		) {
			this->fadeOut = fadeOut;
			}
		
		void apply(Slice<Color> leds) {
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = (unsigned char)((float)leds[i].red*this->fadeOut);
				leds[i].green = (unsigned char)((float)leds[i].green*this->fadeOut);
				leds[i].blue = (unsigned char)((float)leds[i].blue*this->fadeOut);
			}
		}
		
		void tick() {/* Does nothing */}
};

} // end namespace FastRGB