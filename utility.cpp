#include "utility.h"

namespace myNamespace {
	void transform(float& r) {
		/**
		* Input: a reference to a float
		* Output:
		* It represents a linear mapping that maps [-4*255, 4*255] to [0,255]
		* The equation was calculated by having the points transform(-4*255) = 0 and transform(4*255) = 255
		*/
		r = 255 * (r + 4 * 255) / (8 * 255);
	}

	float max(float x, float y) {
		if (x > y) {
			return x;
		}
		return y;
	}

	float min(float x, float y) {
		if (x < y) {
			return x;
		}
		return y;
	}
}
