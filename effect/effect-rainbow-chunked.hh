#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Rainbow pattern that has a step per chunk of LED instead of per led */
class EffectRainbowChunked : public Effect {
	private:
		/** hue from 0-255 */
		float hue = 0;
		/** ammount of increase hue for each tick */
		float hueTickInc;
		/** ammount of increase hue for each chunk in the strip */
		float hueChunkInc;
		/** number of LEDs per chunk */
		unsigned short chunkSize;
		
		Color hslToRGB(float h, float s, float l) {
			// Chroma
			float C = (1.0f - fabs(2.0f * l - 1.0f)) * s;
			// Hue prime
			float hPrime = h*h * 6.0f;
			// Second component
			float X = C * (1.0f - fabs(fmod(hPrime, 2.0f) - 1.0f));
			// Match value
			float m = l - C / 2.0f;

			// Final RGB channels
			float R = 0.0f, G = 0.0f, B = 0.0f;
			
			// Choose components based on hue prime
			if (hPrime < 1.0f) {R = C; G = X; B = 0;}
			else if (hPrime < 2.0f) {R = X; G = C; B = 0;}
			else if (hPrime < 3.0f) {R = 0; G = C; B = X;}
			else if (hPrime < 4.0f) {R = 0; G = X; B = C;}
			else if (hPrime < 5.0f) {R = X; G = 0; B = C;}
			else {R = C; G = 0; B = X;}
			
			Color result;
			result.red   = static_cast<unsigned char>((R + m) * 255.0f);
			result.green = static_cast<unsigned char>((G + m) * 255.0f);
			result.blue  = static_cast<unsigned char>((B + m) * 255.0f);
			return result;
		}
		
	public:
		void next(Slice<Color> leds) {
			float hueTemp = this->hue;
			Color chunkColor = this->hslToRGB(hueTemp, 1, 0.5);
			for (int i = 0; i < leds.length(); i ++) {
				// For each section (that's not the first)
				if (i % this->chunkSize == 0 && i != 0) {
					hueTemp -= this->hueChunkInc;
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
		
		EffectRainbowChunked(float hueTickInc, float hueChunkInc, unsigned short chunkSize) {
			this->hueTickInc = hueTickInc;
			this->hueChunkInc = hueChunkInc;
			this->chunkSize = chunkSize;
		}
};

} // end namespace FastRGB