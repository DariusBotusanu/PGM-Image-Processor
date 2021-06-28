#include "ImageProcessing.h"

namespace myNamespace {
	void ImageProcessing::process(const Image& src, Image& dst) {
		/**
		* Input: reference to an Image objects, src being the original image and dst being the altered iamge
		* Output:
		* The method doesn't do any changes to the original image, hence, the altered image is assigned the original image.
		*/
		dst = src;
	}
}
