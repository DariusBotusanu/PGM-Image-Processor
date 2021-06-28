#include "Image.h"
#include <iostream>
#include "ImageProcessing.h"
#include "GammaCorrection.h"
#include "BrightnessContrast.h"
#include "DrawingModule.h"
#include "Convolution.h"
#include "test.h"
#include <crtdbg.h>


#define _CRTDBG_MAP_ALLOC

using namespace myNamespace;

int main() {
	Image img;
	img.load("./images/casablanca.ascii.pgm");
	//DEFINING SOME POINTS
	Point p1, p2, p3, p4;
	p1 = Point(0, 0);
	p2 = Point(100, 100);
	p3 = Point(100, 50);
	p4 = Point(60, 273);
	//DEFINING SOME RECTANGLES
	Rectangle r1, r2, r3;
	r1 = Rectangle(p1, p2);
	r2 = Rectangle(p3, p2);
	r3 = Rectangle(p1, p4);
	
	//THE DRAWING MODULE
	Image drawCirc, drawLineImg, drawRectangleOne, drawRectangleTwo;
	drawCirc = img;
	drawLineImg = img;
	drawRectangleOne = img;
	drawRectangleTwo = img;
	drawCircle(drawCirc, p2, 109, 10);
	drawCircle(drawCirc, p2, 111, 10);
	drawCircle(drawCirc, p2, 121, 10);
	drawCircle(drawCirc, p2, 131, 10);
	drawCircle(drawCirc, p2, 142, 10);
	drawCircle(drawCirc, p2, 100, 10);
	drawCircle(drawCirc, p2, 101, 10);
	drawCirc.save("./images/processed/drawings/CIRCLE.ascii.pgm");

	drawLine(drawLineImg, p1, p2, 0);
	drawLine(drawLineImg, p1, p3, 0);
	drawLine(drawLineImg, p1, p4, 0);
	drawLineImg.save("./images/processed/drawings/LINE.ascii.pgm");

	drawRectangle(drawRectangleOne, r1, 1);
	drawRectangle(drawRectangleOne, r2, 200);
	drawRectangle(drawRectangleOne, r3, 70);
	drawRectangleOne.save("./images/processed/drawings/Rectangle_1.ascii.pgm");

	drawRectangle(drawRectangleTwo, p1, p2, 1);
	drawRectangle(drawRectangleTwo, p1, p3, 200);
	drawRectangle(drawRectangleTwo, p1, p4, 70);
	drawRectangleTwo.save("./images/processed/drawings/Rectangle_2.ascii.pgm");

	Image drawWhite;
	drawWhite.zeros(1000, 1000);
	Point pwhite;
	pwhite = Point(500, 500);
	drawCircle(drawWhite, pwhite, 10, 255);
	drawCircle(drawWhite, pwhite, 20, 255);
	drawCircle(drawWhite, pwhite, 30, 255);
	drawWhite.save("./images/processed/drawings/drawWhite.ascii.pgm");

	drawCirc.~Image();
	drawLineImg.~Image();
	drawRectangleOne.~Image();
	drawRectangleTwo.~Image();
	
	//THE CONVOLUTIONS
	Image imgConvolutionId, imgConvolutionMean, imgConvolutionGauss, imgConvolutionHor, imgConvolutionVert;
	Convolution conv1, conv2, conv3, conv4, conv5;
	conv1.chooseOption();
	imgConvolutionId = conv1.applyKernel(img);
	conv2.chooseOption();
	imgConvolutionMean = conv2.applyKernel(img);
	conv3.chooseOption();
	imgConvolutionGauss = conv3.applyKernel(img);
	conv4.chooseOption();
	imgConvolutionHor = conv4.applyKernel(img);
	conv5.chooseOption();
	imgConvolutionVert = conv5.applyKernel(img);


	imgConvolutionId.save("./images/processed/convolutions/imgConvolutionId.ascii.pgm");
	imgConvolutionMean.save("./images/processed/convolutions/imgConvolutionMean.ascii.pgm");
	imgConvolutionGauss.save("./images/processed/convolutions/imgConvolutionGauss.ascii.pgm");
	imgConvolutionHor.save("./images/processed/convolutions/imgConvolutionHor.ascii.pgm");
	imgConvolutionVert.save("./images/processed/convolutions/imgConvolutionVert.ascii.pgm");

	conv1.~Convolution();
	conv2.~Convolution();
	conv3.~Convolution();
	conv4.~Convolution();
	conv5.~Convolution();

	imgConvolutionId.~Image();
	imgConvolutionMean.~Image();
	imgConvolutionGauss.~Image();
	imgConvolutionHor.~Image();
	imgConvolutionVert.~Image();

	//GAMMA CORRECTION
	Image g0, g01, g02, g03, g04, g05, g06, g07, g08, g09, g1, g11, g12, g13, g14, g15, g16, g17, g18, g19, g2;
	GammaCorrection gamma09 = GammaCorrection(0.9);
	gamma09.process(img, g09);
	g09.save("./images/processed/gamma/gamma0_9.ascii.pgm");
	GammaCorrection gamma08 = GammaCorrection(0.8);
	gamma08.process(img, g08);
	g08.save("./images/processed/gamma/gamma0_8.ascii.pgm");
	GammaCorrection gamma07 = GammaCorrection(0.7);
	gamma07.process(img, g07);
	g07.save("./images/processed/gamma/gamma0_7.ascii.pgm");
	GammaCorrection gamma06 = GammaCorrection(0.6);
	gamma06.process(img, g06);
	g06.save("./images/processed/gamma/gamma0_6.ascii.pgm");
	GammaCorrection gamma05 = GammaCorrection(0.5);
	gamma05.process(img, g05);
	g05.save("./images/processed/gamma/gamma0_5.ascii.pgm");
	GammaCorrection gamma04 = GammaCorrection(0.4);
	gamma04.process(img, g04);
	g04.save("./images/processed/gamma/gamma0_4.ascii.pgm");
	GammaCorrection gamma03 = GammaCorrection(0.3);
	gamma03.process(img, g03);
	g03.save("./images/processed/gamma/gamma0_3.ascii.pgm");
	GammaCorrection gamma02 = GammaCorrection(0.2);
	gamma02.process(img, g02);
	g02.save("./images/processed/gamma/gamma0_2.ascii.pgm");
	GammaCorrection gamma01 = GammaCorrection(0.1);
	gamma01.process(img, g01);
	g01.save("./images/processed/gamma/gamma0_1.ascii.pgm");
	GammaCorrection gamma0 = GammaCorrection(0);
	gamma07.process(img, g0);
	g0.save("./images/processed/gamma/gamma0_0.ascii.pgm");
	GammaCorrection gamma20 = GammaCorrection(2);
	gamma20.process(img, g2);
	g2.save("./images/processed/gamma/gamma2_0.ascii.pgm");
	GammaCorrection gamma19 = GammaCorrection(1.9);
	gamma19.process(img, g19);
	g19.save("./images/processed/gamma/gamma1_9.ascii.pgm");
	GammaCorrection gamma18 = GammaCorrection(1.8);
	gamma18.process(img, g18);
	g18.save("./images/processed/gamma/gamma1_8.ascii.pgm");
	GammaCorrection gamma17 = GammaCorrection(1.7);
	gamma17.process(img, g17);
	g17.save("./images/processed/gamma/gamma1_7.ascii.pgm");
	GammaCorrection gamma16 = GammaCorrection(1.6);
	gamma16.process(img, g16);
	g16.save("./images/processed/gamma/gamma1_6.ascii.pgm");
	GammaCorrection gamma15 = GammaCorrection(1.5);
	gamma15.process(img, g15);
	g15.save("./images/processed/gamma/gamma1_5.ascii.pgm");
	GammaCorrection gamma14 = GammaCorrection(1.4);
	gamma14.process(img, g14);
	g14.save("./images/processed/gamma/gamma1_4.ascii.pgm");
	GammaCorrection gamma13 = GammaCorrection(1.3);
	gamma16.process(img, g13);
	g13.save("./images/processed/gamma/gamma1_3.ascii.pgm");
	GammaCorrection gamma12 = GammaCorrection(1.2);
	gamma12.process(img, g12);
	g12.save("./images/processed/gamma/gamma1_2.ascii.pgm");
	GammaCorrection gamma11 = GammaCorrection(1.1);
	gamma11.process(img, g11);
	g11.save("./images/processed/gamma/gamma1_1.ascii.pgm");
	GammaCorrection gamma1 = GammaCorrection(1);
	gamma1.process(img, g1);
	g1.save("./images/processed/gamma/gamma1_0.ascii.pgm");

	g0.~Image();
	g01.~Image();
	g02.~Image();
	g03.~Image();
	g04.~Image();
	g05.~Image();
	g06.~Image();
	g07.~Image();
	g08.~Image();
	g09.~Image();
	g1.~Image();
	g11.~Image();
	g12.~Image();
	g13.~Image();
	g14.~Image(); 
	g15.~Image();
	g16.~Image();
	g17.~Image();
	g18.~Image();
	g19.~Image();
	g2.~Image();


	//BRIGHTNESS CONTRAST
	Image brightcon00, brightcon05, brightcon10, brightcon15, brightcon20, brightcon25, brightcon30;
	BrightnessContrast bc00, bc05, bc010, bc10, bc15, bc20, bc25, bc30;
	bc00 = BrightnessContrast(0, 0);
	bc00.process(img, brightcon00);
	brightcon00.save("./images/processed/brightcon/b0c0.ascii.pgm");
	bc05 = BrightnessContrast(0, 5);
	bc05.process(img, brightcon05);
	brightcon05.save("./images/processed/brightcon/b0c5.ascii.pgm");
	bc10 = BrightnessContrast(1, 0);
	bc10.process(img, brightcon10);
	brightcon10.save("./images/processed/brightcon/b1c0.ascii.pgm");
	bc15 = BrightnessContrast(1, 5);
	bc15.process(img, brightcon15);
	brightcon15.save("./images/processed/brightcon/b1c5.ascii.pgm");
	bc20 = BrightnessContrast(2, 0);
	bc20.process(img, brightcon20);
	brightcon20.save("./images/processed/brightcon/b2c0.ascii.pgm");
	bc25 = BrightnessContrast(2, 5);
	bc25.process(img, brightcon25);
	brightcon25.save("./images/processed/brightcon/b2c5.ascii.pgm");
	bc30 = BrightnessContrast(3, 0);
	bc30.process(img, brightcon30);
	brightcon30.save("./images/processed/brightcon/b3c0.ascii.pgm");

	brightcon00.~Image();
	brightcon05.~Image();
	brightcon10.~Image();
	brightcon15.~Image();
	brightcon20.~Image();
	brightcon25.~Image();
	brightcon30.~Image();

	
	test_all();


	_CrtDumpMemoryLeaks();
	return 0;
}