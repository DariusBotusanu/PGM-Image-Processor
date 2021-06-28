#include "BrightnessContrast.h"

namespace myNamespace {
	BrightnessContrast::BrightnessContrast() {
		/**
		* Input: -
		* Output: -
		* The cosntructor of the class BrightnessContrast
		*/
		m_contrast = 1;
		m_brightness = 0;
	}

	BrightnessContrast::BrightnessContrast(float c, int b) {
		/**
		* Input: - c - contrast; b - brightness
		* Output: -
		* The parameterized cosntructor of the class BrightnessContrast
		*/
		m_contrast = c;
		m_brightness = b;
	}

	void BrightnessContrast::process(Image& src, Image& dst) {
		/**
		* Input: reference to an Image objects, src being the original image and dst being the altered iamge
		* Output:
		* The override of the virtual function "process" from ImageProcessing class.
		*/
		dst.release();
		dst.allocate(src.width(), src.height());
		for (unsigned int i = 0; i < src.height(); i++) {
			for (unsigned int j = 0; j < src.width(); j++) {
				Point pt = Point(i, j);
				if ((src.at(pt) * m_contrast + m_brightness) > 255) {
					dst.at(pt) = 255;
				}
				else {
					dst.at(pt) = src.at(pt) * m_contrast + m_brightness;
				}
			}
		}
	}
}

