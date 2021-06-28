#include "test.h"
#include "Image.h"
#include "Point.h"
#include "Size.h"
#include "ImageProcessing.h"
#include "utility.h"
#include "math.h"
#include "Convolution.h"
#include <limits>
#include <assert.h>

namespace myNamespace {
	void test_all() {
		//Image testing
		//Testing cosntructor
		Image img;
		assert((img.width()) == 0);
		assert((img.height()) == 0);
		//Testing assignment operator and parameterized builder
		img = Image(3, 4);
		assert((img.width()) == 3);
		assert((img.height()) == 4);

		Image img2;
		img2 = Image(3, 4);

		//We fill the data of the image
		unsigned char k = 1;
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				img.at(i, j) = k + 2;
				img2.at(i, j) = k + 1;
			}
		}

		//Testing method .at
		Point pi = Point(1, 1);
		assert((img.at(1, 1)) == 3);
		assert((img.at(pi)) == 3);
		assert((img2.at(1, 1)) == 2);
		assert((img2.at(pi)) == 2);


		//Testing operators +,-,* on the Image class
		Image imgAddition, imgSubtraction, imgMultiplication;
		imgAddition = img + img2; //img changes!
		imgSubtraction = img - img2; //img becomes what it was before the las toperation
		imgMultiplication = img * img2; //entries of img should become 6
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				assert((imgAddition.at(i, j)) == 5);
				assert((imgSubtraction.at(i, j)) == 3);
				assert((imgMultiplication.at(i, j)) == 6);
			}
		}

		//Test reading and writing on .pgm files
		assert((img2.load(".unexistingImage.pgm")) == false);
		assert((img2.load("./testing/testRead.pgm")) == true);
		assert((img2.save("./testing/testWrite.pgm")) == true);

		//Test release
		img.release();
		assert((img.width()) == 0);
		assert((img.height()) == 0);

		//Test zeros
		img.zeros(3, 4);
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				assert((img.at(i, j)) == 0);
			}
		}

		//Test ones
		img.ones(3, 4);
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				assert((img.at(i, j)) == 0);
			}
		}

		//Test Point
		//Test constructors and assignment operator =, plus coordinate getters
		Point p;
		assert((p.xCoord()) == 0);
		assert((p.yCoord()) == 0);

		p = Point(3, 4);
		assert((p.xCoord()) == 3);
		assert((p.yCoord()) == 4);

		//Test translate
		p.translate(1);
		assert((p.xCoord()) == 4);
		assert((p.yCoord()) == 5);

		p.translate(-1);
		assert((p.xCoord()) == 3);
		assert((p.yCoord()) == 4);

		Point p1(70, 70), p2(70, 70);
		assert((p1 == p2) == true);
		assert((p == p2) == false);

		//Test Rectangle
		//Test constructors and assignment operator =, plus width, height getters
		Rectangle r;
		assert((r.width()) == 0);
		assert((r.height()) == 0);
		Point topLeft(0, 0), bottomRight(1, 2);
		r = Rectangle(topLeft, 3, 4);
		assert((r.width()) == 3);
		assert((r.height()) == 4);
		r = Rectangle(topLeft, bottomRight);
		assert((r.width()) == 2);
		assert((r.height()) == 1);

		//Test + and - operators
		r + 2;
		assert((r.topLeft()) == Point(2, 2));
		r - 1;
		assert((r.topLeft()) == Point(1, 1));

		//Test intersection
		Point ti, bi, tk, bk;
		ti = Point(0, 0);
		bi = Point(3, 3);
		tk = Point(1, 1);
		bk = Point(2, 2);
		Rectangle ri, rk, cap, cup;
		ri = Rectangle(ti, bi);
		rk = Rectangle(tk, bk);
		cap = ri & rk;
		assert((cap.topLeft()) == Point(1, 1));
		assert((cap.width()) == 1);
		assert((cap.height()) == 1);
		//Test union
		cup = ri | rk;
		assert((cup.topLeft()) == Point(0, 0));
		assert((cup.width()) == 3);
		assert((cup.height()) == 3);




		//Test Size
		//Test cosntructors and assignment operator =. Testing the getters as well
		Size s;
		assert((s.sizeWidth()) == 0);
		assert((s.sizeHeight()) == 0);

		s = Size(19, 19);
		assert((s.sizeWidth()) == 19);
		assert((s.sizeHeight()) == 19);

		//Test ImageProcessing
		ImageProcessing ip;
		Image toProcess, appliedProc;
		toProcess = Image(3, 4);
		int l = 0;
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				toProcess.at(i, j) = l++;
			}
		}
		ip.process(toProcess, appliedProc);
		l = 0;
		for (int i = 0; i < img.height(); i++) {
			for (int j = 0; j < img.width(); j++) {
				assert((appliedProc.at(i, j)) == l++);
			}
		}

		//Test the lienar mapping transform
		float num;
		num = 4 * 255;
		transform(num);
		assert(num == 255);
		num = -4 * 255;
		transform(num);
		assert(num == 0);
		num = 65;
		transform(num);
		assert(abs(num - 135.625) < numeric_limits<float>::epsilon());

		//Test Convolution
		//Test constructors and assignment operator =
		Convolution conv;
		//int testKernel[3][3];
		assert((conv.w()) == 0);
		assert((conv.h()) == 0);
		conv = Convolution(3, 3);
		assert((conv.w()) == 3);
		assert((conv.h()) == 3);
		//conv.readKernel("./kernels/gaussianBlur.txt");



		cout << "Testing done" << endl;
	}
}
