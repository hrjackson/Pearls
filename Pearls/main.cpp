//
//  main.cpp
//  Pearls
//
//  Created by Henry Jackson on 17/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#include "Mobius.h"
#include "Plot.h"


void explore( Plot &pl, Mobius a, Mobius b,
             Circle Ca, Circle Cb, Circle CA, Circle CB, int maxLevel);

void recursiveExplore( Plot &pl,
                      Mobius map,
                      int j,
                      Mobius gens[4],
                      Circle circs[4],
                      int inverse[4],
                      int level,
                      int maxLevel);

//const Scalar cols[4] = {Scalar(255,255,255), Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255)};

const Scalar colScale(int level, int maxLevel);

int main() {


    int width = 2880*5;
    int height = 1800*5;
    int scale = height*0.28;
    int maxLevel = 14;
    Plot pl(width, height, Point(width/2, height/2), scale, Scalar(10,10,0));
    
    /*
    double s = 0.005;
    double t = 0.995;
    double radSmall = (t-s)/2.0;
    double radBig = (1.0/s - 1.0/t)/2.0;
    std::complex<double> centreSmall = s + radSmall;
    std::complex<double> centreBig = 1/t + radBig;
    */
    
    std::complex<double> k = 2;
    std::complex<double> v = 1;
    std::complex<double> I(0,1);
    
    std::complex<double> y = 2.0/( v*(k+1.0/k) );
    std::complex<double> x = sqrt(1.0 + pow(y,2));
    std::complex<double> u = sqrt(1.0 + pow(v,2));
    //std::complex<double> c = 2/(y*v);
//    double k = (( 1.0 + sqrt( 1.0 - pow(y*v, 2.0) ) )/(y*v)).real();
    double radReal = (1.0/y).real();
    double radImag = (k/v).real();
    std::complex<double> centreReal = x/y;
    std::complex<double> centreImag = I*k*u/v;
    
    
    Mobius a(u, I*k*v, -I*v/k, u);
    Mobius b(x, y, y, x);
    Circle Ca{radImag, centreImag};
    Circle Cb{radReal, centreReal};
    Circle CA{radImag, -centreImag};
    Circle CB{radReal, -centreReal};
    
    //pl.circle(Ca.centre, Ca.radius, Scalar(255,255,255));
    //pl.circle(CA.centre, CA.radius, Scalar(255,255,255));
    
    explore(pl, a, b, Ca, Cb, CA, CB, maxLevel);
    
    //pl.show();
    pl.output("output.jpg");
    //cv::waitKey( 0 );
    return 0;
}


void explore( Plot &pl, Mobius a, Mobius b,
             Circle Ca, Circle Cb, Circle CA, Circle CB, int maxLevel){
    Mobius A = a.inverse();
    Mobius B = b.inverse();
    Mobius gens[4] = {a, b, A, B};
    int inverse[4] = {2, 3, 0, 1};
    int level = 0;
    Circle circs[4] = {Ca, Cb, CA, CB};
    for(int i=0; i<4; ++i){
        pl.circle(circs[i].centre, circs[i].radius, colScale(level, maxLevel));
        //pl.show();
        recursiveExplore(pl, gens[i], i, gens, circs, inverse, level, maxLevel);
    }
}

void recursiveExplore( Plot &pl,
                      Mobius map,
                      int j,
                      Mobius gens[4],
                      Circle circs[4],
                      int inverse[4],
                      int level,
                      int maxLevel) {
    Circle image;
    for (int i=0; i<4; ++i){
        if(i != inverse[j]){
            image = map.circleImage(circs[i]);
            pl.circle(image.centre, image.radius, colScale(level, maxLevel));
            //pl.show();
            //cv::waitKey(0);
            if( level < maxLevel ){
                recursiveExplore(pl, map.after(gens[i]), i, gens, circs, inverse, level+1, maxLevel);
            }
        }
    }
}

const Scalar colScale(int level, int maxLevel){
    double proportion = double(level)/double(maxLevel);
    double col = 255*sqrt(proportion);
    int colour = (int)col;
    return Scalar(colour,colour,0);
}
