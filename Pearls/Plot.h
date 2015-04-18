/*
 * Plot.h
 *
 *  Created on: 11 Apr 2015
 *      Author: henry
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <complex>
#include "Mobius.h"

using namespace cv;
using namespace std;

class Plot {
private:
	Mat image;
	Mat colGradient;
	int width;
	int height;
	Point origin;
	int scale;
	Point currentPos;
public:
	Plot(int width, int height, Point origin, int scale);
	virtual ~Plot();
	void circle(std::complex<double> centre, double radius, const Scalar& colour);
	void line(std::complex<double> point, double thickness, const Scalar& colour);
	void changePosition(std::complex<double> point);
	void show();
    void output(const string& filename);
	int getScale();
};

#endif /* PLOT_H_ */
