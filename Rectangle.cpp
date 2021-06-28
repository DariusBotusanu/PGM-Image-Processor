#include "Rectangle.h"

namespace myNamespace {
	Rectangle::Rectangle() {
		/**
		* Input:
		* Output:
		* The default constructor of the class rectangle
		*/
		m_topLeft = Point();
		m_width = 0;
		m_height = 0;
		m_data = nullptr;
	}

	Rectangle::Rectangle(Point topLeft, unsigned int width, unsigned int height) {
		/**
		* Input: Point topLeft - the upper left corner of the rectangle; width - the width of the rectangle; height - the height of the rectangle;
		* Output:
		* A parameterized constructor of the class Rectangle
		*/
		m_topLeft = topLeft;
		m_width = width;
		m_height = height;
		allocate(width, height);
	}

	Rectangle::Rectangle(Point topLeft, Point bottomRight) {
		/**
		* Input: Point topLeft - the upper left corner of the rectangle; Point bottomRight - the buttom right corner of the rectangle;
		* Output:
		* A parameterized constructor of the class Rectangle
		*/
		m_topLeft = topLeft;
		m_height = bottomRight.xCoord() - topLeft.xCoord();
		m_width = bottomRight.yCoord() - topLeft.yCoord();
		allocate(m_width, m_height);
	}

	Rectangle& Rectangle::operator=(const Rectangle& other) {
		/**
		* Input: constant reference to a Rectangle object
		* Output: cosntant reference to a Rectangle object
		* The assignment operator of the class Rectangle
		*/
		m_topLeft = other.m_topLeft;
		m_width = other.m_width;
		m_height = other.m_height;
		m_data = other.m_data;
		return *this;
	}

	void Rectangle::allocate(unsigned int w, unsigned int h) {
		/**
		* Input: unsigned int w, unsigned int h
		* Output:
		* It changes the m_width and m_height to w and h respectively.
		* It allocates the space of m_data.
		*/
		if (m_data == nullptr) {
			m_width = w;
			m_height = h;
			m_data = new Point * [m_height];
			for (unsigned int i = 0; i < m_height; i++) {
				m_data[i] = new Point[m_width];
			}
		}
	}

	void Rectangle::release() {
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

	void Rectangle::operator+(unsigned int v) {
		/**
		* Input: unsgined int v
		* Output:
		* Translates the rectangle with the vector (v,v)
		*/
		Point bottomRight = Point(m_width + m_topLeft.xCoord(), m_height + m_topLeft.yCoord());
		m_topLeft.translate(v);
		bottomRight.translate(v);
		m_height = bottomRight.xCoord() - m_topLeft.xCoord();
		m_width = bottomRight.yCoord() - m_topLeft.yCoord();
	}

	void Rectangle::operator-(unsigned int v) {
		/**
		* Input: unsgined int v
		* Output:
		* Translates the rectangle with the vector (-1)*(v,v)
		*/
		Point bottomRight = Point(m_width + m_topLeft.xCoord(), m_height + m_topLeft.yCoord());
		m_topLeft.translate((-1) * v);
		bottomRight.translate((-1) * v);
		m_height = bottomRight.xCoord() - m_topLeft.xCoord();
		m_width = bottomRight.yCoord() - m_topLeft.yCoord();
	}

	Rectangle Rectangle::operator&(Rectangle& other) {
		/**
		* Input: reference to an object of class Rectangle
		* Output: reference to an object of class Rectangle
		* Overload function for the operator & which gives the intersection of two rectangles
		*/
		//These will be the vertices of the first triangle
		Point topLeftFirst = m_topLeft;
		Point bottomRightFirst = Point(m_width + m_topLeft.xCoord(), m_height + m_topLeft.yCoord());

		//These will be the vertices of the second triangle
		Point topLeftSecond = other.m_topLeft;
		Point bottomRightSecond = Point(other.m_width + other.m_topLeft.xCoord(), other.m_height + other.m_topLeft.yCoord());


		Point topLeftIntersection = Point(max(topLeftFirst.xCoord(), topLeftSecond.xCoord()), max(topLeftFirst.yCoord(), topLeftSecond.yCoord()));
		Point bottomRightIntersection = Point(min(bottomRightFirst.xCoord(), bottomRightSecond.xCoord()), min(bottomRightFirst.yCoord(), bottomRightSecond.yCoord()));

		if (topLeftIntersection.xCoord() > bottomRightIntersection.xCoord()) {
			Rectangle r = Rectangle();
			return r;
		}
		if (topLeftIntersection.yCoord() > bottomRightIntersection.yCoord()) {
			Rectangle r = Rectangle();
			return r;
		}
		Point& top = topLeftIntersection;
		Point& bot = bottomRightIntersection;

		Rectangle r = Rectangle(top, bot);
		return r;
	}


	Rectangle Rectangle::operator|(Rectangle& other) {
		/**
		* Input: reference to an object of class Rectangle
		* Output: reference to an object of class Rectangle
		* Overload function for the operator & which gives the union of two rectangles
		* The return rectangle could contain points which are not in any of the two rectangles, therefore we give those points the values NULL_VALUE
		*/
		//These will be the vertices of the first triangle
		Point topLeftFirst = m_topLeft;
		Point bottomRightFirst = Point(m_width + m_topLeft.xCoord(), m_height + m_topLeft.yCoord());

		//These will be the vertices of the second triangle
		Point topLeftSecond = other.m_topLeft;
		Point bottomRightSecond = Point(other.m_width + other.m_topLeft.xCoord(), other.m_height + other.m_topLeft.yCoord());

		Point topLeftCup = Point(min(topLeftFirst.xCoord(), topLeftSecond.xCoord()), min(topLeftFirst.yCoord(), topLeftSecond.yCoord()));
		Point bottomRightCup = Point(max(bottomRightFirst.xCoord(), bottomRightSecond.xCoord()), max(bottomRightFirst.yCoord(), bottomRightSecond.yCoord()));

		Point topLeftIntersection = Point(max(topLeftFirst.xCoord(), topLeftSecond.xCoord()), max(topLeftFirst.yCoord(), topLeftSecond.yCoord()));
		Point bottomRightIntersection = Point(min(bottomRightFirst.xCoord(), bottomRightSecond.xCoord()), min(bottomRightFirst.yCoord(), bottomRightSecond.yCoord()));

		Rectangle r = Rectangle(topLeftCup, bottomRightCup);

		/*
		for (unsigned int i = topLeftCup.xCoord(); i <= bottomRightCup.xCoord(); i++) {
			for (unsigned int j = topLeftCup.yCoord(); j <= bottomRightCup.yCoord(); j++) {
				//The points above the intersection
				if (i < topLeftIntersection.xCoord()) {
					r.m_data[i][j].xCoord() = NULL_VALUE;
					r.m_data[i][j].yCoord() = NULL_VALUE;
				}
				//The points to the left of the intersection
				if (j < topLeftIntersection.yCoord()) {
					r.m_data[i][j].xCoord() = NULL_VALUE;
					r.m_data[i][j].yCoord() = NULL_VALUE;
				}
				//The points under the intersection
				if (i > bottomRightIntersection.xCoord()) {
					r.m_data[i][j].xCoord() = NULL_VALUE;
					r.m_data[i][j].yCoord() = NULL_VALUE;
				}
				//The points to the right of the intersection
				if (j > bottomRightIntersection.yCoord()) {
						r.m_data[i][j].xCoord() = NULL_VALUE;
						r.m_data[i][j].yCoord() = NULL_VALUE;
				}
			}
		}
		*/

		return r;
	}
}

