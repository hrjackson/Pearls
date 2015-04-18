/*
 * Mobius.h
 *
 *  Created on: 15 Apr 2015
 *      Author: henry
 */

#ifndef MOBIUS_H_
#define MOBIUS_H_

#include <complex>

#define cpx std::complex<double>

struct Circle {
	double radius;
	cpx centre;
};

class Mobius {
public:
	// Holds the matrix (a,b; c,d), in that order.
	cpx matrix[4];
	Mobius(cpx matrix[4]);
	Mobius(cpx a, cpx b, cpx c, cpx d);

	virtual ~Mobius();
	Circle circleImage(Circle preImage);
	cpx pointImage(cpx point);
	Mobius after(Mobius before);
    Mobius inverse();
};

#endif /* MOBIUS_H_ */
