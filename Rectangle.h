#pragma once
#include "Point.h"

namespace myNamespace {
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(Point topLeft, unsigned int width, unsigned int height);
		Rectangle(Point topLeft, Point bottomRight);
		Rectangle& operator=(const Rectangle& other);

		void operator+(unsigned int v);
		void operator-(unsigned int v);

		void allocate(unsigned int w, unsigned int h);
		void release();

		Point& topLeft() { return m_topLeft; }
		unsigned int& width() { return m_width; }
		unsigned int& height() { return m_height; }

		Point& at(unsigned int i, unsigned int j) { return m_data[i][j]; }

		Rectangle operator&(Rectangle& other);
		Rectangle operator|(Rectangle& other);


	private:
		Point m_topLeft;
		unsigned int m_width;
		unsigned int m_height;
		Point** m_data;
	};
}


