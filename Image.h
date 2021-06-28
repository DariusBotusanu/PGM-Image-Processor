#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"

namespace myNamespace {
	using namespace std;

	class Image
	{
	public:
		Image();
		Image(unsigned int w, unsigned int h);
		Image(Image& other);
		Image& operator=(const Image& other);
		~Image();

		//unsigned int width() { return m_width; }
		//unsigned int height() { return m_height; }

		bool load(std::string imagePath);
		bool save(std::string imagePath);
		Image operator+(Image& img);
		Image operator-(Image& i);
		Image operator*(Image& i);

		friend std::ostream& operator<<(std::ostream& os, Image& dt);
		bool isEmpty() const;
		void release();
		void allocate(unsigned int w, unsigned int h);
		Size size() const;
		bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		unsigned int width() const { return m_width; }
		unsigned int height() const { return m_height; }

		unsigned char& at(unsigned int x, unsigned int y) { return m_data[x][y]; }
		unsigned char& at(Point pt) { return m_data[pt.xCoord()][pt.yCoord()]; }

		unsigned char* row(int y) { return *(m_data + y); }

		Image zeros(unsigned int width, unsigned int height);
		Image ones(unsigned int width, unsigned int height);
	private:
		unsigned char** m_data;
		unsigned int m_width;
		unsigned int m_height;
	};


}
