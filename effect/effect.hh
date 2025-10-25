#pragma once

#include <ArxSmartPtr.h>

#include "../color.hh"
#include "../slice/slice.hh"

namespace FastRGB {

class Effect {
	public:
		virtual bool next(Slice<Color> current, unsigned char hue);
		virtual ~Effect() {};
};

} // end namespace FastRGB