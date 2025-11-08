#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

/** Simple rainbow pattern */
class EffectRainbow : public Effect {
	protected:
		/** hue from 0-255 */
		float hue = 0;
		/** ammount of increase hue for each tick */
		float hueTickInc;
		/** ammount of increase hue for each LED in the strip */
		float hueLEDInc;
		
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
			for (int i = 0; i < leds.length(); i ++) {
				leds[i] = this->hslToRGB(hueTemp, 1, 0.5);
				hueTemp -= this->hueLEDInc;
				if (hueTemp < 0) {hueTemp += 1;}
			}
		}
		
		void tick() {
			this->hue += this->hueTickInc;
			if (this->hue > 1) {this->hue --;}
		}
		
		EffectRainbow(float hueTickInc, float hueLEDInc) {
			this->hueTickInc = hueTickInc;
			this->hueLEDInc = hueLEDInc;
		}
};

} // end namespace FastRGB