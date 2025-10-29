#pragma once

#include <ArxSmartPtr.h>

#include "../color.hh"
#include "../slice/slice.hh"

namespace FastRGB {

class Effect {
	public:
		/** Updates the data in the Slice of Color objects */
		virtual void next(Slice<Color> leds);
		/** Increments some arbitrary state in the effect */
		virtual void tick();
		
		virtual ~Effect() {};
};

} // end namespace FastRGB