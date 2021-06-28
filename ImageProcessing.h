#pragma once
#include "Image.h"
#include "math.h"

namespace myNamespace {
	class ImageProcessing
	{
	public:
		virtual void process(const Image& src, Image& dst);
	};
}


