#include "GammaCorrection.h"

namespace myNamespace{
	GammaCorrection::GammaCorrection() {
		/**
		* Input: -
		* Output: -
		* The cosntructor of the class GammaCorrection
		*/
		m_gamma = 0;
	}

	GammaCorrection::GammaCorrection(float gamma) {
		/**
		* Input: - gamma - the exponent to which we raise the pixels at.
		* Output: -
		* The parameterized cosntructor of the class GammaCorrection.
		*/
		m_gamma = gamma;
	}

	void GammaCorrection::process(Image& src, Image& dst) {
		/**
		* Input: reference to an Image objects, src being the original image and dst being the altered iamge
		* Output:
		* The override of the virtual function "process" from ImageProcessing class.
		*/
		dst.release();
		dst.allocate(src.width(), src.height());
		for (unsigned int i = 0; i < src.height(); i++) {
			for (unsigned int j = 0; j < src.width(); j++) {
				if (pow(src.at(i, j), m_gamma) > 255) {
					dst.at(i, j) = 255;
				}
				else if (m_gamma == 0) {
					dst.at(i, j) = 1;
				}
				else {
					dst.at(i, j) = (unsigned char)((unsigned int)((int)pow(src.at(i, j), m_gamma)));
				}
			}
		}
	}
}
