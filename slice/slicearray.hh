#pragma once

namespace FastRGB {

/** Class which slices up an Array in a memory-safe manner */
template <typename T>
class SliceArray {
	public:
		/** Stores the data */
		T * data = nullptr;
		/** Pointer to number of SliceArray objects point to data */
		unsigned * dataRef = nullptr;
		/** Array length */
		unsigned arrayLength = 0;
		
		SliceArray() {}
		
		SliceArray(unsigned arrayLength) {
			this->data = new T[arrayLength];
			this->dataRef = new unsigned(1);
			this->arrayLength = arrayLength;
		}
		
		SliceArray(const SliceArray & r)
		: data(r.data), dataRef(r.dataRef), arrayLength(r.arrayLength) {
			if (this->dataRef) {(*this->dataRef) ++;}
		}
		
		SliceArray & operator=(const SliceArray & r) {
			if (this == &r) {return *this;}
			
			if (this->dataRef && --(*this->dataRef) == 0) {
				delete[] this->data;
                delete this->dataRef;
            }
			
			// Copy everything
			this->data = r.data;
			this->dataRef = r.dataRef;
			this->arrayLength = r.arrayLength;
			if (this->dataRef) {(*this->dataRef) ++;}
			
			return *this;
		}
		
		~SliceArray() {
			if (this->dataRef && --(*this->dataRef) == 0) {
				delete[] this->data;
				delete this->dataRef;
			}
		}
};

}