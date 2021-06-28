#include "Point.h"
namespace myNamespace {
	Point::Point() {
		/**
		* Input:
		* Output:
		* The constructor of the class point.
		*/
		m_x = 0;
		m_y = 0;
	}

	Point::Point(unsigned int x, unsigned int y) {
		/**
		* Input: x - the column coordinate, y - the row coordinate
		* Output:
		* The parameterized constructor of the class point.
		*/
		m_x = x;
		m_y = y;
	}

	Point& Point::operator=(const Point& other) {
		/**
		* Input: cosntant reference to an object of class Point
		* Output: a reference to a Point object
		* The assignment operator of the class Point.
		*/
		m_x = other.m_x;
		m_y = other.m_y;
		return *this;
	}

	void Point::translate(unsigned int v) {
		/**
		* Input: unsigned int v
		* Output: -
		* This function translates the point with the vector (v, v)
		*/
		m_x += v;
		m_y += v;
	}

	bool Point::operator==(Point p) {
		/**
		* Input: an object of class Point
		* Output: true/false
		* This function returns true if two points are the same. Otherwise it returns false;
		*/
		if ((m_x == p.m_x) && (m_y == p.m_y)) {
			return true;
		}
		else {
			return false;
		}
	}

	ostream& operator<<(ostream& os, const Point& pt) {
		/**
		* Input: reference to ostream operator, constant reference to a Point object which we want to print
		* Output: a reference to ostream oeprator <<
		* This overload allows the printing of a Point object in a specified manner
		*/
		os << "(" << pt.m_x << "," << pt.m_y << ")\n";
		return os;
	}

	istream& operator>>(istream& input, Point& pt) {
		/**
		* Input: reference to istream operator, reference to a Point object which we want to read
		* Output: a reference to istream operator >>
		* This overload allows the reading of a Point object
		*/
		cout << "Coordinate x: ";
		input >> pt.m_x;
		cout << endl;
		cout << "Coordinate y: ";
		input >> pt.m_y;
		cout << endl;
		return input;
	}
}
