#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Rainbow pattern that has a step per chunk of LED instead of per led */
class EffectRainbowChunked : public EffectRainbow {
	private:
		// Includes all protected from EffectRainbow
		
		/** number of LEDs per chunk */
		unsigned short chunkSize;
		
	public:
		void next(Slice<Color> leds) {
			float hueTemp = this->hue;
			Color chunkColor = this->hslToRGB(hueTemp, 1, 0.5);
			for (int i = 0; i < leds.length(); i ++) {
				// For each section (that's not the first)
				if (i % this->chunkSize == 0 && i != 0) {
					hueTemp -= this->hueLEDInc;
					if (hueTemp < 0) {hueTemp += 1;}
					chunkColor = this->hslToRGB(hueTemp, 1, 0.5);
				}
				
				// Copy the chunk's color
				leds[i] = chunkColor;
			}
		}
		
		void tick() {
			this->hue += this->hueTickInc;
			if (this->hue > 1) {this->hue --;}
		}
		
		EffectRainbowChunked(float hueTickInc, float hueChunkInc, unsigned short chunkSize)
		: EffectRainbow(hueTickInc, hueChunkInc) {
			this->chunkSize = chunkSize;
		}
};

} // end namespace FastRGB