#include "Image.h"

namespace myNamespace {
	Image::Image() {
		/**
		* Input:
		* Output:
		* Default constructor of the class Image. It assigns m_data the null pointer and m_width, m_height the value 0;
		*/
		m_data = nullptr;
		m_width = 0;
		m_height = 0;
	}

	Image::Image(unsigned int w, unsigned int h) {
		/**
		* Input: unsigned int w, unsigned int h
		* Output:
		* Parameterized constructor of the class Image.
		* It assigns m_width, m_height the values w and h respectively.
		* It allocates space for m_data on the heap.
		*/
		m_width = w;
		m_height = h;
		m_data = new unsigned char* [h];
		for (unsigned int i = 0; i < h; i++) {
			m_data[i] = new unsigned char[w];
		}
		/*
		for (unsigned int i = 0; i < h; i++) {
			for (unsigned int j = 0; j < w; j++) {
				m_data[i] = 0;
			}
		}
		*/
	}

	Image::Image(Image& other) {
		/**
		* Input: a reference to an Image object
		* Output:
		* Copy constructor of the class Image.
		*/
		//this->release();

		m_width = other.m_width;
		m_height = other.m_height;
		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			m_data[i] = new unsigned char[m_width];
		}
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				m_data[i][j] = other.m_data[i][j];
			}
		}
	}

	void Image::release() {
		/**
		* Input:
		* Output:
		* It deallocates the space of m_data. If m_data == nullptr, it does nothing.
		*/
		if (this->m_data != nullptr) {
			for (unsigned int i = 0; i < m_height; i++) {
				delete[] m_data[i];
			}
			delete[] m_data;
		}
		m_data = nullptr;
		this->m_width = 0;
		this->m_height = 0;
	}

	void Image::allocate(unsigned int w, unsigned int h) {
		/**
		* Input: unsigned int w, unsigned int h
		* Output:
		* It changes the m_width and m_height to w and h respectively.
		* It allocates the space of m_data.
		*/
		if (m_data == nullptr) {
			m_width = w;
			m_height = h;
			m_data = new unsigned char* [m_height];
			for (unsigned int i = 0; i < m_height; i++) {
				m_data[i] = new unsigned char[m_width];
			}
		}
	}

	Image& Image::operator=(const Image& other) {
		/**
		* Input: a constant reference to an Image object
		* Output:
		* The overload for the assignment operator.
		* It assigns the objct the values of other.
		*/
		release();
		allocate(other.width(), other.height());
		/*
		m_width = other.m_width;
		m_height = other.m_height;
		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			m_data[i] = new unsigned char[m_width];
		}
		*/
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				m_data[i][j] = other.m_data[i][j];
			}
		}
		return *this;
	}

	Image::~Image() {
		/**
		* Input:
		* Output:
		* The destructor for the class Image;
		*/
		this->release();
	}



	bool Image::load(std::string imagePath) {
		/**
		* Input: std::string - the path (and name) of the file we want to read
		* Output: true/false
		* This function searches for a file.
		* - If the file is not found, it returns false.
		* - Otherwise: it reads the width, height and data of the image and stores it in the object which called the method.
		*/
		this->release();

		ifstream file;
		file.open(imagePath);
		if (!file) {
			return false;
		}
		string type;
		short int max_pixel;
		file >> type; // It reads P2, we drop it
		file >> m_width; //We read the width of the image
		file >> m_height; //We read the height of the image
		file >> max_pixel; //It reads 255, we drop it

		//Deleting old array

		//Allocating space for the actual image
		m_data = new unsigned char* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			m_data[i] = new unsigned char[m_width];
		}


		unsigned int** num = new unsigned int* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			num[i] = new unsigned int[m_width];
		}

		while (file) {
			for (unsigned int i = 0; i < m_height; i++) {
				for (unsigned int j = 0; j < m_width; j++) {
					file >> num[i][j];
					m_data[i][j] = (unsigned char)num[i][j];
				}
			}
		}

		for (unsigned int i = 0; i < m_height; i++) {
			delete[] num[i];
		}
		delete[] num;
		num = nullptr;
		file.close();
		return true;
	}

	bool Image::save(std::string imagePath) {
		/**
		* Input: std::string - the path (and name) of the file we want to write
		* Output: true/false
		* This function opens a new file to write.
		* - If the file is not created, it returns false.
		* - Otherwise: it prints the image in a pgm format
		*/
		ofstream file;
		file.open(imagePath);
		if (!file) {
			return false;
		}
		file << "P2" << endl; //The type of the image, 1st line
		file << m_width << " " << m_height << endl; //Width and height, 2nd line
		file << "255" << endl; //Maximum pixel value, 3rd line

		//We print the pixel values of the image into the file;
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				file << (unsigned int)this->at(i, j) << " ";
			}
			file << endl;
		}

		file.close();
		return true;
	}

	Image Image::operator+(Image& img) {
		/**
		* Input: a reference to an iamge
		* Output: the modified Image to which we apply the operator
		* This is the overload + operator for the class Image
		* - If the dimensions of the images differ, it throws an exception
		* - Otherwise: it adds pairwise the elements of the images, trimming them down to the interval [0, 255] if necessary.
		*/
		// We make sure the "matrices(arrays of arrays)" are compatible with addition
		if ((m_width != img.m_width) || (m_height != img.m_height)) {
			throw exception();
		}
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				m_data[i][j] += img.at(i, j);
				if (m_data[i][j] > 255) { //The maximum pixel value is 255
					m_data[i][j] = 255;
				}
			}
		}
		return *this;
	}

	Image Image::operator-(Image& img) {
		/**
		* Input: a reference to an iamge
		* Output: the modified Image to which we apply the operator
		* This is the overload - operator for the class Image
		* - If the dimensions of the images differ, it throws an exception
		* - Otherwise: it subtracts pairwise the elements of the images, trimming them down to the interval [0, 255] if necessary.
		*/
		// We make sure the "matrices(arrays of arrays" are compatible with subtraction
		if ((m_width != img.m_width) || (m_height != img.m_height)) {
			throw exception();
		}
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				m_data[i][j] -= img.at(i, j);
				if (m_data[i][j] < 0) { //The minimum pixel value is 0
					m_data[i][j] = 0;
				}
			}
		}
		return *this;
	}

	Image Image::operator*(Image& img) {
		/**
		* Input: a reference to an iamge
		* Output: the modified Image to which we apply the operator
		* This is the overload * operator for the class Image
		* - If the dimensions of the images differ, it throws an exception
		* - Otherwise: it multiplies pairwise the elements of the images, trimming them down to the interval [0, 255] if necessary.
		*/
		// We make sure the "matrices(arrays of arrays" are compatible with pairwise multiplication
		if ((m_width != img.m_width) || (m_height != img.m_height)) {
			throw exception();
		}
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				m_data[i][j] *= img.at(i, j);
				if (m_data[i][j] > 255) { //The maximum pixel value is 255
					m_data[i][j] = 255;
				}
			}
		}
		return *this;
	}

	ostream& operator<<(std::ostream& os, Image& dt) {
		/**
		* Input: reference to ostream operator, reference to an Image object which we want to print
		* Output: a reference to ostream oeprator <<
		* This overload allows the printing of an Image object in a specified manner
		*/
		os << "Width: " << dt.m_width << endl;
		os << "Height: " << dt.m_height << endl;
		for (unsigned int i = 0; i < dt.m_height; i++) {
			for (unsigned int j = 0; j < dt.m_width; j++) {
				os << (unsigned int)dt.m_data[i][j] << setw(3) << " ";
			}
			os << endl;
		}
		return os;
	}

	bool Image::isEmpty() const {
		/**
		* Input:
		* Output: true/false
		* This method returns true if m_data is doesn't have any elements (i.e. m_data is the null pointer). Otherwise, it returns false.
		*/
		if (m_data == nullptr) {
			return true;
		}
		return false;
	}

	Size Image::size() const {
		/**
		* Input:
		* Output: an object of type Size - represents the size of the image
		* This method returns the size of the Image object which calls it.
		*/
		Size s = Size(m_width, m_height);
		return s;
	}


	Image Image::zeros(unsigned int width, unsigned int height) {
		/**
		* Input: unsigned int width, unsigned int height - the new width and height of the Image object which calls this method.
		* Output: an object of type Image populated only with zeros
		* This method changes the width and height of the image which calls it, and it populates m_data with zeros.
		*/
		this->release();
		m_width = width;
		m_height = height;
		m_data = new unsigned char* [height];
		for (unsigned int i = 0; i < height; i++) {
			m_data[i] = new unsigned char[width];
		}
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				m_data[i][j] = 0;
			}
		}
		return *this;
	}

	Image Image::ones(unsigned int width, unsigned int height) {
		/**
		* Input: unsigned int width, unsigned int height - the new width and height of the Image object which calls this method.
		* Output: an object of type Image populated only with 1=ones
		* This method changes the width and height of the image which calls it, and it populates m_data with ones.
		*/
		this->release();
		m_width = width;
		m_height = height;
		m_data = new unsigned char* [height];
		for (unsigned int i = 0; i < height; i++) {
			m_data[i] = new unsigned char[width];
		}
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				m_data[i][j] = 1;
			}
		}
		return *this;
	}


	bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
		/**
		* Input: - a reference to an Image roiImg -> It represents a portion of the image which calls the object
		*		 - unsigned int x, unsigned int y -> the coordinates of the upper left point of roiImg
		*		 - unsigned int width, unsigned int height -> the width and height of roiImg
		* Output: true - if the region of interest is within bounds
		*		  false - otherwise
		* This method checks if the wanted region of interest is within bounds and throws an exception if it is not.
		* Otherwise it makes a deep copy of the portion of the original image and assigns it to roiImg
		*/
		if ((x + width > this->m_width) || (y + height > this->m_height)) {
			cout << "ROI out of bounds!" << endl;
			return false;
		}

		roiImg.release(); // We delete the old array data

		//We change roiImg to match the width and height of the ROI
		roiImg.m_width = width;
		roiImg.m_height = height;

		//We allocate space for the new array (which will be a region of "this"
		roiImg.m_data = new unsigned char* [height];
		for (unsigned int i = 0; i < width; i++) {
			roiImg.m_data[i] = new unsigned char[width];
		}

		for (unsigned int i = x; i < x + height; i++) {
			for (unsigned int j = y; j < y + width; j++) {
				// Pointer arithmetics which binds the specific values of the original image to the values of the ROI (roiImg)
				*(*(roiImg.m_data + i - x) + j - y) = *(*(m_data + i) + j);
			}
		}
		return true;
	}

}
