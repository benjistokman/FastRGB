#pragma once

#include "effect.hh"

namespace FastRGB {

/* Fades in and out as per a currSine wave function */
class EffectPulsing : public Effect {
	private:
		/* Theta (radians), incremented by tick() */
		float theta;
		/* Amount to increase theta by per tick */
		float thetaTick;
		/* Amount to increase theta by per unique color */
		float thetaColor;
		/* Low end of currSine wave, must be [0,1] */
		float low = 0;
		/* High end of the currSine wave, must be [0,1] */
		float high = 1;
		/* Sequential color writes, 0 is ∞ */
		unsigned numDuplicates;
		
	public:
		/* Creates an effect that applies a dimming currSine wave to a series
		   @NOTE you probably want to apply another effect first before using
				 just this one */
		EffectPulsing(
			/* Amount to increase theta by per tick() */
			float thetaTick,
			/* Amount to increase theta by per unique color */
			float thetaColor,
			/* Lowst brightness to apply to any given Color
			   If this isn't in the range of [0,1] it will be set to the default
			   of 0. */
			float low,
			/* Highest brightness to apply to any given Color
			  If this isn't in the range of [0,1] it will be set to the default
			  of 1. */
			float high,
			/* How many Color objects to write a unique color to before
			   incrementing theta by thetaColor. Useful for making groups of
			   LEDs the same color.
			   @param 0 and 1 are considered the same thing
			   @param 0 is interpreted as ∞ */
			unsigned numDuplicates
		) {
			this->thetaTick = thetaTick;
			if (0 < low < 1) {this->low = low;}
			if (0 < high < 1) {this->high = low;}
			this->high = high;
			this->numDuplicates = numDuplicates;
		}
		
		void apply(Slice<Color> leds) {
			int duplicate = 0;
			float currTheta = this->theta;
			
			for (int i = 0; i < leds.length(); i ++) {
				// Calculate current sine
				float currSine = ((sin(currTheta) + 1) / 2)*(high-low)+low;
				
				// Update color
				leds[i].green = (unsigned char)((float)leds[i].green*currSine);
				leds[i].red = (unsigned char)((float)leds[i].red*currSine);
				leds[i].blue = (unsigned char)((float)leds[i].blue*currSine);
				
				// currSine will only ever update if numDuplicates is 1 or more
				if (this->numDuplicates > 0) {
					// Update it
					duplicate ++;
					// Update currSine and reset
					if (duplicate >= this->numDuplicates) {
						currTheta += this->thetaColor;
						duplicate = 0;
					}
				}
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