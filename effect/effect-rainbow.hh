#pragma once

#include "effect.hh"

#include "../convert/hsltorgb.hh"

namespace FastRGB {

/* Simple rainbow pattern */
class EffectRainbow : public Effect {
	protected:
		/* hue from 0-1 */
		float hue = 0;
		/* amount of increase hue for each tick */
		float hueTickInc;
		/* amount of increase hue for each LED in the strip */
		float hueColorInc;
		/* Sequential color writes, 0 is ∞ */
		unsigned numDuplicates;
		
	public:
		
		/* Writes Colors in a spectrum of the HSL hue, with saturation at 100%
		   and luminance at 50% */
		EffectRainbow(
			/* How much to increment the hue [0, 255] per tick() */
			float hueTickInc,
			/* How much to increment the hue per unique color */
			float hueColorInc,
			/* How many Color objects to write a unique color to before
			   incrementing theta by thetaColor. Useful for making groups of
			   LEDs the same color.
			   @param 0 is interpreted as ∞ */
			unsigned numDuplicates
		) {
			this->hueTickInc = hueTickInc;
			this->hueColorInc = hueColorInc;
			this->numDuplicates = numDuplicates;
		}
		
		void apply(Slice<Color> leds) {
			float currHue = this->hue;
			int duplicate = 0;
			
			for (int i = 0; i < leds.length(); i ++) {
				// Update color
				leds[i] = hslToRGB(currHue, 1, 0.5);
				
				// currSine will only ever update if numDuplicates is 1 or more
				if (this->numDuplicates > 0) {
					// Update it
					duplicate ++;
					// Update currSine and reset
					if (duplicate >= this->numDuplicates) {
						currHue += this->hueColorInc;
						if (currHue > 1) {currHue -= 1;}
						duplicate = 0;
					}
				}
			}
		}
		
		void tick() {
			this->hue += this->hueTickInc;
			if (this->hue > 1) {this->hue --;}
			if (this->hue < 0) {this->hue ++;}
		}
};

} // end namespace FastRGB