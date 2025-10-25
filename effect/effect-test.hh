#pragma once

#include <ArxSmartPtr.h>

#include "effect.hh"

namespace FastRGB {

class EffectTest : Effect {
	public:
		bool next(Slice<Color> current, unsigned char hue) {
			for (int i = 0; i < current.length(); i ++) {
				current[i].red = hue;
			}
			return true;
		}
};

} // end namespace FastRGB