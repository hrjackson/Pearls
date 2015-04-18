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


    int width = 10000;
    int height = 2000;
    int scale = height*0.9;
    int maxLevel = 14;
    Plot pl(width, height, Point(width/2, height/2), scale);
    
    double s = 0.005;
    double t = 0.995;
    double radSmall = (t-s)/2.0;
    double radBig = (1.0/s - 1.0/t)/2.0;
    std::complex<double> centreSmall = s + radSmall;
    std::complex<double> centreBig = 1/t + radBig;
    
    Mobius a(s+t, -2*s*t, -2, s+t);
    Mobius b(s+t, 2, 2*s*t, s+t);
    Circle Ca{radSmall, -centreSmall};
    Circle Cb{radBig, centreBig};
    Circle CA{radSmall, centreSmall};
    Circle CB{radBig, -centreBig};
    
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
    int col = 255*level/maxLevel;
    return Scalar(col,col,0);
}
