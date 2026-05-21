#pragma once

#include "../color.hh"
#include "../slice/slice.hh"

namespace FastRGB {

/* Parent class with virtual methods each effect must implement */
class Effect {
	public:
		/* Updates the data in the Slice of Color objects */
		virtual void apply(Slice<Color> leds);
		/* Increments some arbitrary state in the effect */
		virtual void tick();
		
		virtual ~Effect() {};
};

} // end namespace FastRGB