#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Fades in and out as per a sine wave function */
class EffectPulsing : public Effect {
	private:
		/** Color to pulse */
		Color color;
		/** Theta (radians) */
		float theta;
		/** Amount to increase theta by per tick */
		float thetaTick;
		
	public:
		EffectPulsing(Color color, float thetaTick) {
			this->color = color;
			this->thetaTick = thetaTick;
		}
		
		void next(Slice<Color> leds) {
			float sine = (sin(this->theta) + 1) / 2;
			
			Color currColor;
			currColor.red = (unsigned char)(this->color.red * sine);
			currColor.green = (unsigned char)(this->color.green * sine);
			currColor.blue = (unsigned char)(this->color.blue * sine);
			
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = currColor.red;
				leds[i].green = currColor.green;
				leds[i].blue = currColor.blue;
			}
		}
		
		void tick() {
			this->theta += this->thetaTick;
			if (this->theta > 6.283185307) {
				this->theta -= 6.283185307;
			}
		}
};

} // end namespace FastRGB