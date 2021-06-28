#include "Convolution.h"

namespace myNamespace {
	Convolution::Convolution() {
		/**
		* Input: -
		* Output: -
		* This is the constructor of the class Convolution.
		*/
		m_w = 0;
		m_h = 0;
		kernel = nullptr;
	}

	Convolution::Convolution(unsigned int w, unsigned int h) {
		/**
		* Input: w - thr number of columns, h - the number of rows
		* Output: -
		* This is the parameterized constructor of the class Convolution.
		*/
		m_w = w;
		m_h = h;
		kernel = new int* [h];
		for (unsigned int i = 0; i < h; i++) {
			kernel[i] = new int[w];
		}
	}

	Convolution& Convolution::operator=(const Convolution& other) {
		/**
		* Input: - a constant reference to an object of the class Convolution
		* Output: -
		* This is the assignment operator of the class Convolution.
		*/
		this->release();
		m_w = other.m_w;
		m_h = other.m_h;
		kernel = new int* [m_h];
		for (unsigned int i = 0; i < m_h; i++) {
			kernel[i] = new int[m_w];
		}
		for (unsigned int i = 0; i < m_h; i++) {
			for (unsigned int j = 0; j < m_w; j++) {
				kernel[i][j] = other.kernel[i][j];
			}
		}
		return *this;
	}

	void Convolution::release() {
		/**
		* Input: -
		* Output: -
		* This method is used to deallocate the memory of the kernel.
		*/
		if (kernel != nullptr) {
			for (unsigned int i = 0; i < m_h; i++) {
				delete[] kernel[i];
			}
			delete[] kernel;
			kernel = nullptr;
		}
		m_w = 0;
		m_h = 0;
	}

	Convolution::~Convolution() {
		/**
		* Input: -
		* Output: -
		* The destructor of an object of class Convolution.
		*/
		this->release();
	}

	Image Convolution::applyKernel(Image& img) {
		/**
		* Input: Image& - a reference to an image oject
		* Output: - Image - an image object
		* This function applies the convolution to a given image and returns the result in a different image object;
		*/
		Image dst;
		dst.zeros(img.width(), img.height());
		//cout << (-1)*((int)(m_h / 2)) << ", " << (-1) * ((int)(m_w / 2)) <<endl; //I AM SO PROUD OF THIS!!!
		float denum = 0;
		for (int i = 0; i < (int)m_h; i++) {
			for (int j = 0; j < (int)m_w; j++) {
				denum += (float)kernel[i][j];
			}
		}
		dst = Image(img.width(), img.height());
		for (int y = m_h / 2; y < (int)(img.height() - (m_h / 2)); y++) {
			for (int x = m_w / 2; x < (int)(img.width() - (m_w / 2)); x++) {
				float newPix = 0;
				for (int dy = (-1) * ((int)(m_h / 2)); dy <= (int)(m_h / 2); dy++) {
					for (int dx = (-1) * ((int)(m_w / 2)); dx <= (int)(m_w / 2); dx++) {
						newPix += (img.at(y + dy, x + dx) * kernel[dy + (int)(m_h / 2)][dx + (int)m_w / 2]);
					}
				}
				if (denum != 0) {
					dst.at(y - (int)(m_h / 2), x - (int)(m_w / 2)) = (int)(newPix / denum);
				}
				else {
					transform(newPix);
					dst.at(y - (int)(m_h / 2), x - (int)(m_w / 2)) = (int)(newPix);
				}
			}
		}
		return dst;
	}

	void Convolution::showMenu() {
		/**
		* Input: -
		* Output: -
		* This function prints the available options for the kernel.
		*/
		cout << "Choose from the following:" << endl;
		cout << "	Identity kernel (1)\n";
		cout << "	Mean Blur (2)\n";
		cout << "	Gaussian Blur (3)\n";
		cout << "	Horizontal Sobel (4)\n";
		cout << "	Vertical Sobel (5)\n";
	}

	void Convolution::readKernel(string filePath) {
		/**
		* Input: std::string - represents the path of the file we want to read
		* Output: -
		* This function reads the kernel from a given text-file
		*/
		ifstream file;
		file.open(filePath);
		file >> m_h;
		file >> m_w;

		if (kernel != nullptr) {
			for (unsigned int i = 0; i < m_h; i++) {
				delete[] kernel[i];
			}
			delete[] kernel;
			kernel = nullptr;
		}

		kernel = new int* [m_h];
		for (unsigned int i = 0; i < m_h; i++) {
			kernel[i] = new int[m_w];
		}

		for (unsigned int i = 0; i < m_h; i++) {
			for (unsigned int j = 0; j < m_w; j++) {
				file >> kernel[i][j];
			}
		}
	}

	void Convolution::chooseOption() {
		/**
		* Input: -
		* Output: -
		* This function allows the user to select the kernel he wants.
		*/
		int option;
		showMenu();
		cin >> option;
		if (option == 1) {
			readKernel("./kernels/identity.txt");
		}
		if (option == 2) {
			readKernel("./kernels/meanBlur.txt");
		}
		if (option == 3) {
			readKernel("./kernels/gaussianBlur.txt");
		}
		if (option == 4) {
			readKernel("./kernels/horizontalSobel.txt");
		}
		if (option == 5) {
			readKernel("./kernels/verticalSobel.txt");
		}
	}

	ostream& operator<<(std::ostream& os, Convolution& dt) {
		/**
		* Input: -std:: ostream& operator, Convolution&
		* Output: - ostream&
		* This function allows the printing of an object from the Convolution class in a specified manner.
		*/
		os << "Width: " << dt.m_w << endl;
		os << "Height: " << dt.m_h << endl;
		for (unsigned int i = 0; i < dt.m_h; i++) {
			for (unsigned int j = 0; j < dt.m_w; j++) {
				os << dt.kernel[i][j] << setw(3) << " ";
			}
			os << endl;
		}
		return os;
	}
}
