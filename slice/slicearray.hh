#pragma once

#include <ArxSmartPtr.h>

namespace FastRGB {

/** Class which slices up an Array in a memory-safe manner */
template <typename T>
class SliceArray {
	public:
		/** Stores the data */
		T * data = nullptr;
		/** Array length */
		unsigned arrayLength;
		
		SliceArray(unsigned arrayLength) {
			this->data = new T[arrayLength];
			this->arrayLength = arrayLength;
		}
		
		~SliceArray() {delete[] this->data;}
};

}