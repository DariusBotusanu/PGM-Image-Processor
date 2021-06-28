#include "DrawingModule.h"

namespace myNamespace {
	void drawCircle(Image& img, Point center, int radius, unsigned char color) {
		for (unsigned int i = 0; i < img.height(); i++) {
			for (unsigned int j = 0; j < img.width(); j++) {
				if (pow(i - center.xCoord(), 2) + pow(j - center.yCoord(), 2) == (radius * radius)) {
					img.at(i, j) = color;
				}
			}
		}
	}

	void drawLine(Image& img, Point p1, Point p2, unsigned char color) {

		if (p1.xCoord() == p2.xCoord()) {
			for (unsigned int i = p1.yCoord(); i <= p1.yCoord(); i++) {
				img.at(p1.xCoord(), i) = color;
			}
		}
		else if (p1.yCoord() == p2.yCoord()) {
			for (unsigned int i = p1.xCoord(); i <= p1.xCoord(); i++) {
				img.at(i, p1.yCoord()) = color;
			}
		}
		else {
			for (unsigned int i = 0; i < img.height(); i++) {
				for (unsigned int j = 0; j < img.width(); j++) {
					Point p;
					p = Point(i, j);
					int value = (i - p1.xCoord()) * (p2.yCoord() - p1.yCoord()) - (j - p1.yCoord()) * (p2.xCoord() - p1.xCoord());
					if ((value == 0) && (i <= p2.xCoord()) && (j <= p2.yCoord())) {
						img.at(p) = color;
					}

				}
			}
		}
	}

	void drawRectangle(Image& img, Rectangle r, unsigned char color) {
		if ((r.topLeft().xCoord() + r.height() > img.height()) || (r.topLeft().yCoord() + r.width() > img.width())) {
			throw exception("Rectangle out of bounds!");
		}
		unsigned int iStart = r.topLeft().xCoord();
		unsigned int iStop = r.topLeft().xCoord() + r.height();
		unsigned int jStart = r.topLeft().yCoord();
		unsigned int jStop = r.topLeft().yCoord() + r.width();



		for (unsigned int i = iStart; i <= iStop; i++) {
			for (unsigned int j = jStart; j <= jStop; j++) {
				img.at(i, j) = color;
			}
		}

	}


	void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
		Rectangle r = Rectangle(tl, br);
		unsigned int iStart = r.topLeft().xCoord();
		unsigned int iStop = r.topLeft().xCoord() + r.height();
		unsigned int jStart = r.topLeft().xCoord();
		unsigned int jStop = r.topLeft().xCoord() + r.width();
		for (unsigned int i = iStart; i <= iStop; i++) {
			for (unsigned int j = jStart; j <= jStop; j++) {
				img.at(i, j) = color;
			}
		}
	}
}

