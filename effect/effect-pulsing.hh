#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Fades in and out as per a sine wave function */
class EffectPulsing : public Effect {
	private:
		Color color;
		unsigned char thisTick = 0;
		
	public:
		EffectPulsing(Color color) {this->color = color;}
		
		void next(Slice<Color> leds) {
			Color currColor = this->color;
			
			float radians = float(this->thisTick) / 128 * 6.283185307;
			float sine = (sin(radians) + 1) / 2.25 + (1/9);
			
			currColor.red = (unsigned char)(currColor.red * sine);
			currColor.green = (unsigned char)(currColor.green * sine);
			currColor.blue = (unsigned char)(currColor.blue * sine);
			
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = currColor.red;
				leds[i].green = currColor.green;
				leds[i].blue = currColor.blue;
			}
		}
		
		void tick() {this->thisTick ++;}
};

} // end namespace FastRGB