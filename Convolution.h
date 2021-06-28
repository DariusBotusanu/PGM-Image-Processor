#pragma once
#include "ImageProcessing.h"
#include "utility.h"

namespace myNamespace {
	class Convolution : public ImageProcessing {
	public:
		Convolution();
		Convolution(unsigned int w, unsigned int h);
		Convolution& operator=(const Convolution& other);
		~Convolution();

		void release();
		void showMenu();
		void readKernel(string filePath);
		void chooseOption();

		unsigned int w() { return m_w; }
		unsigned int h() { return m_h; }
		int** getKernel() { return kernel; }

		friend std::ostream& operator<<(std::ostream& os, Convolution& dt);

		Image applyKernel(Image& img);

	private:
		unsigned int m_w;
		unsigned int m_h;
		int** kernel;
	};
}

