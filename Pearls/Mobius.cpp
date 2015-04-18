/*
 * Mobius.cpp
 *
 *  Created on: 15 Apr 2015
 *      Author: henry
 */

#include "Mobius.h"

Mobius::Mobius(std::complex<double> matrix[4]) {
	for(int i=0; i<4; ++i){
		this->matrix[i] = matrix[i];
	}
}

Mobius::Mobius(cpx a, cpx b, cpx c, cpx d) {
	matrix[0] = a;
	matrix[1] = b;
	matrix[2] = c;
	matrix[3] = d;
	cpx sqrtDet = sqrt(abs(a*d - b*c));
	for(int i=0; i<4; ++i){
		matrix[i] = matrix[i]/sqrtDet;
	}
}

Mobius::~Mobius() {
	// TODO Auto-generated destructor stub
}

Circle Mobius::circleImage(Circle preImage) {
	Circle image;
	cpx denomConj = matrix[3]/matrix[2] + preImage.centre;
	cpx denom(denomConj.real(), -denomConj.imag());
	cpx z = preImage.centre - ( pow(preImage.radius, 2)/denom );
	image.centre = pointImage(z);
	image.radius = abs(image.centre
			           - pointImage(preImage.centre + preImage.radius));
	return image;
}

cpx Mobius::pointImage(cpx z) {
	cpx result = (matrix[0]*z + matrix[1])/
			     (matrix[2]*z + matrix[3]);
	return result;
}

Mobius Mobius::after(Mobius before) {
	cpx result[4];
	cpx tmp;
    result[0] = matrix[0]*before.matrix[0] + matrix[1]*before.matrix[2];
    result[1] = matrix[0]*before.matrix[1] + matrix[1]*before.matrix[3];
    result[2] = matrix[2]*before.matrix[0] + matrix[3]*before.matrix[2];
    result[3] = matrix[2]*before.matrix[1] + matrix[3]*before.matrix[3];
	Mobius composition(result);
	return composition;
}

Mobius Mobius::inverse() {
    Mobius inv(matrix[3], -matrix[1], -matrix[2], matrix[0]);
    return inv;
}
