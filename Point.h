#pragma once
#include <iostream>
#define NULL_VALUE 999 

namespace myNamespace {
	using namespace std;

	class Point
	{
	public:
		Point();
		Point(unsigned int x, unsigned int y);
		Point& operator=(const Point& other);

		unsigned int xCoord() { return m_x; }
		unsigned int yCoord() { return m_y; }

		void translate(unsigned int v);

		bool operator==(Point p);

		friend ostream& operator<<(ostream& os, const Point& pt);
		friend istream& operator>>(istream& input, Point& pt);


	private:
		unsigned int m_x;
		unsigned int m_y;
	};
}


