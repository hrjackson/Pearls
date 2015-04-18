/*
 * Plot.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: henry
 */

#include "Plot.h"

Plot::Plot(int width, int height, Point origin, int scale)
:width(width), height(height), origin(origin), scale(scale),
 currentPos(origin){
	// Origin is in original scale, scale sets pixels per unit
	image = Mat::zeros( height, width, CV_8UC3 );

};

Plot::~Plot() {
	// TODO Auto-generated destructor stub
};

void Plot::circle(std::complex<double> centre, double radius,
		          const Scalar& colour) {
	int rad = radius*scale;
	int centreX = centre.real()*scale;
	int centreY = centre.imag()*scale;
	cv::circle(image, origin+Point(centreY, centreX), rad, colour, -1);
};

void Plot::changePosition(std::complex<double> point){

}

void Plot::show(){
	cv::imshow("window", image);
}

void Plot::output(const string& filename) {
    cv::imwrite(filename, image);
}

int Plot::getScale(){
	return scale;
}
