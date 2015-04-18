//
//  MobiusTest.cpp
//  Pearls
//
//  Created by Henry Jackson on 17/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "catch.hpp"

#include "Mobius.h"


TEST_CASE( "Mobius class tested", "[M obius]"){
    Circle unit{1, 0};
    std::complex<double> point{1,1};
    Circle offset{3, point};
    
    SECTION( "Testing identity" ) {
        Mobius id(1,0,0,1);
        Circle unitImage = id.circleImage(unit);
        Circle offsetImage = id.circleImage(offset);
        
        REQUIRE( id.matrix[0] == 1.0 );
        REQUIRE( id.matrix[1] == 0.0 );
        REQUIRE( id.matrix[2] == 0.0 );
        REQUIRE( id.matrix[3] == 1.0 );
        REQUIRE( unitImage.centre == 0.0 );
        REQUIRE( unitImage.radius == 1.0 );
        REQUIRE( offsetImage.centre == point );
        REQUIRE( offsetImage.radius == 3.0 );
    }
    
    SECTION( "Testing shifts" ) {
        Mobius mob(1,point,0,1);
        Circle unitImage = mob.circleImage(unit);
        Circle offsetImage = mob.circleImage(offset);
        
        REQUIRE( unitImage.centre == point );
        REQUIRE( unitImage.radius == 1.0 );
        REQUIRE( offsetImage.centre == 2.0*point );
        REQUIRE( offsetImage.radius == 3.0 );
    }
    
    SECTION( "Testing scalings" ) {
        Mobius mob(2,0,0,1);
        Circle unitImage = mob.circleImage(unit);
        Circle offsetImage = mob.circleImage(offset);
        
        REQUIRE( mob.matrix[0] == 2/sqrt(2.0) );
        REQUIRE( mob.matrix[3] == 1/sqrt(2.0) );
        
        REQUIRE( unitImage.centre == 0.0 );
        REQUIRE( unitImage.radius == 2.0 );
        REQUIRE( offsetImage.centre == 2.0*point );
        REQUIRE( offsetImage.radius == 6.0 );
    }
    
    SECTION( "Testing identity" ) {
        Mobius mob(8, 1, 4, 5);
        Mobius inv = mob.inverse();
        
        REQUIRE( inv.matrix[0] == 5.0/6.0 );
        REQUIRE( inv.matrix[1] == -1.0/6.0 );
        REQUIRE( inv.matrix[2] == -4.0/6.0 );
        REQUIRE( inv.matrix[3] == 8.0/6.0 );
        
        REQUIRE( mob.after(inv).matrix[0] == 1.0 );
        REQUIRE( mob.after(inv).matrix[1] == 0.0 );
        REQUIRE( mob.after(inv).matrix[2] == 0.0 );
        REQUIRE( mob.after(inv).matrix[3] == 1.0 );
        
        REQUIRE( inv.after(mob).matrix[0] == 1.0 );
        REQUIRE( inv.after(mob).matrix[1] == 0.0 );
        REQUIRE( inv.after(mob).matrix[2] == 0.0 );
        REQUIRE( inv.after(mob).matrix[3] == 1.0 );
    }
    
    SECTION( "Testing special transformation") {
        double s = 0.4;
        double t = 0.8;
        Mobius mob(s+t, -2*s*t, -2, s+t);
        Circle unitImage = mob.circleImage(unit);
        Circle offsetImage = mob.circleImage(offset);
        
        REQUIRE( unitImage.centre == 0.0 );
        REQUIRE( unitImage.radius == 2.0 );
        REQUIRE( offsetImage.centre == 2.0*point );
        REQUIRE( offsetImage.radius == 6.0 );
    }
    
    SECTION( "Testing inversion" ) {
        
    }
}