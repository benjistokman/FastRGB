#pragma once

namespace FastRGB {

/** Stores a 24-bit RGB color */
class Color {
	// This object is a class to provide for potential future methods while
	// still acting like a struct (with public members)
	public:
		unsigned char green;
		unsigned char red;
		unsigned char blue;
};

} // end namespace FastRGB