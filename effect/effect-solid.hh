#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Solid color */
class EffectSolid : public Effect {
	private:
		Color color;
		
	public:
		EffectSolid(Color color) {this->color = color;}
		EffectSolid(unsigned char r, unsigned char g, unsigned char b) {
			this->color.red = r;
			this->color.green = g;
			this->color.blue = b;
		}
		
		void next(Slice<Color> leds) {
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = this->color.red;
				leds[i].green = this->color.green;
				leds[i].blue = this->color.blue;
			}
		}
		
		void tick() {/* Does nothing */}
};

} // end namespace FastRGB