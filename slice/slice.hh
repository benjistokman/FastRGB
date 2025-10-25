#pragma once

#include <ArxSmartPtr.h>

#include "slicearray.hh"

namespace FastRGB {

/** Class which slices up an Array in a memory-safe manner */
template <typename T>
class Slice {
	private:
		/** Smart pointer to heap data to mock memory managed evironment */
		std::shared_ptr<SliceArray<T>> parentArray = nullptr;
		/** Stores a pointer to the base of the slice */
		T * array = nullptr;
		/** Length of slice */
		unsigned arrayLength = 0;
		/** If this slice is valid */
		bool valid = false;
		
	public:
		/** Constructor which makes its own array */
		Slice(unsigned arrayLength) {
			this->parentArray = std::shared_ptr<SliceArray<T>>(
				new SliceArray<T>(arrayLength)
			);
			this->array = parentArray.get()->data;
			this->arrayLength = arrayLength;
			this->valid = true;
		}
		
		/** Invalid */
		Slice() {}
		
		/** Slice specifying all fields (used for copying) */
		Slice(
			std::shared_ptr<SliceArray<T>> parentArray,
			T * array,
			unsigned arrayLength,
			bool valid
		) {
			this->parentArray = parentArray;
			this->array = array;
			this->arrayLength = arrayLength;
			this->valid = valid;
		}
		
		/** Get slice of this array */
		Slice<T> slice(unsigned start, unsigned length) {
			if (start + length > this->arrayLength) {return Slice();}
			
			return Slice(
				this->parentArray,
				this->array + start,
				length,
				true
			);
		}
		
		/** Returns length of array */
		unsigned length() {return this->arrayLength;}
		/** Returns if this slice object points to a valid slice */
		bool isValid() {return this->valid;}
		
		/** Array dereference operator */
		T & operator[](unsigned index) {
			return this->array[index];}
};

}