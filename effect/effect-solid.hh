#pragma once

#include "effect.hh"

namespace FastRGB {

/* Solid color */
class EffectSolid : public Effect {
	private:
		Color color;
		
	public:
		/* Writes a single color */
		EffectSolid(Color color) {this->color = color;}
		
		void apply(Slice<Color> leds) {
			for (int i = 0; i < leds.length(); i ++) {
				leds[i].red = this->color.red;
				leds[i].green = this->color.green;
				leds[i].blue = this->color.blue;
			}
		}
		
		void tick() {/* Does nothing */}
};

} // end namespace FastRGB