#pragma once

namespace FastRGB {

/** Class which slices up an Array in a memory-safe manner */
template <typename T>
class Slice {
	private:
		/** Pointer to start of heap array for memory safety purposes */
		T * baseArray = nullptr;
		/** Pointer to counter on heap for memory safety purposes */
		unsigned * baseArrayRefCount = nullptr;
		
		/** Stores a pointer to the base of the slice */
		T * array = nullptr;
		/** Length of slice */
		unsigned arrayLength = 0;
		
		/** Deletes the two heap items */
		void deleteHeap() {
			if (this->baseArray) {delete[] this->baseArray;}
			if (this->baseArrayRefCount) {delete this->baseArrayRefCount;}
		}
		/** Increments this->dataRef */
		void incRefCount() {
			if (this->baseArrayRefCount) {(*this->baseArrayRefCount) ++;}
		}
		/** Decrements this->dataRef and deletes heap object if reference
			counter == 0 */
		void decRefCount() {
			if (this->baseArrayRefCount) {(*this->baseArrayRefCount) --;}
			else {return;}
			if (*this->baseArrayRefCount == 0) {
				this->deleteHeap();
			}
		}
		
	public:
		/** Invalid */
		Slice() {}
		
		/** Constructor which makes its own array */
		Slice(unsigned arrayLength) {
			this->baseArray = new T[arrayLength];
			this->baseArrayRefCount = new unsigned(1);
			this->array = this->baseArray;
			this->arrayLength = arrayLength;
		}
		
		/** Slice specifying all fields (used for copying) */
		Slice(
			T * baseArray,
			unsigned * baseArrayRefCount,
			T * array,
			unsigned arrayLength
		) {
			this->baseArray = baseArray;
			this->baseArrayRefCount = baseArrayRefCount;
			this->incRefCount();
			this->array = array;
			this->arrayLength = arrayLength;
		}
		
		/** Copy operator */
		Slice(const Slice & r)
		: baseArray(r.baseArray), baseArrayRefCount(r.baseArrayRefCount),
		  array(r.array), arrayLength(r.arrayLength) {
			// Just increment the copied counter
			this->incRefCount();
		}
		
		/** operator= */
		Slice & operator=(const Slice & r) {
			if (this == &r) {return *this;}
			this->decRefCount();
			
			// Copy everything
			this->baseArray = r.baseArray;
			this->baseArrayRefCount = r.baseArrayRefCount;
			this->array = r.array;
			this->arrayLength = r.arrayLength;
			// Copied counter
			this->incRefCount();
			
			return *this;
		}
		
		~Slice() {this->decRefCount();}
		
		/** Get slice of this array */
		Slice<T> slice(unsigned start, unsigned length) const {
			if (start + length > this->arrayLength) {return Slice();}
			
			return Slice(
				this->baseArray,
				this->baseArrayRefCount,
				this->array + start,
				length
			);
		}
		
		/** Returns length of array */
		unsigned length() const {return this->arrayLength;}
		/** Returns if this slice object points to a valid slice */
		bool isValid() const {return (this->array != nullptr);}
		
		/** Array dereference operator */
		T & operator[](unsigned index) const {
			return this->array[index];
		}
};

}