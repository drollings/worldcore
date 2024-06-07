//
// C++ Implementation: coord
//
// Description:
//
//
// Author: Daniel Rollings <dasher@zenonline.com>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <math.h>
#include "coord.hpp"

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;

// Precomputed constants for degrees/radians conversion, and for our arbitrary 16-bit angle measurement.
const double PI = 3.1415926535897932384626433832795028841968;
const double TWOPI = 2.0 * PI;
const double HALFPI = PI / 2.0;
const double QUARTERPI = PI / 4.0;

const double DEGREES_TO_RADIANS = PI / 180.0;
const double MINUTES_TO_RADIANS = PI / 10600.0;

const double RADIANS_TO_DEGREES = 180.0 / PI;
const double RADIANS_TO_MINUTES = 10600.0 / PI;

// Basic unit conversion routines
double	DegreesToRadians(double d)		{	return d * DEGREES_TO_RADIANS;	}
double	RadiansToDegrees(double r)		{	return r * RADIANS_TO_DEGREES;	}
double	Radius(const coord &c)			{	return sqrt( c.vars.x*c.vars.x + c.vars.y*c.vars.y + c.vars.z*c.vars.z );	}

// FIXME - These have horrible rounding errors.  The fact that the differences after conversion are usually just
// a meter means that they aren't completely unusable, 

inline double &	Round(double &d)
{
	long long t = d*1000;
	d = (double)t / 1000.0;
	return d;
}

coord &	coord::operator= (coordSphere const &c)
{
	double sinPhi = sin(c.vars.phi);
	if (c.vars.radius == 0) {
		vars.x = vars.y = vars.z = 0;
	} else {
		vars.x = c.vars.radius * cos(c.vars.theta) * sinPhi;
		vars.y = c.vars.radius * sin(c.vars.theta) * sinPhi;
		vars.z = c.vars.radius * cos(c.vars.phi);
		Round(vars.x);
		Round(vars.y);
		Round(vars.z);
	}
	return *this;
}

coordSphere & coordSphere::operator = (const coord &c)
{
	double r = Radius(c);
	if (c.vars.x || c.vars.y || c.vars.z) {
		vars.radius = r;
		vars.theta = c.vars.x ? atan(c.vars.y / c.vars.x) : 0.0;
		vars.phi = vars.radius ? acos(c.vars.z / r) : 0.0;
	} else {
		vars.radius = vars.theta = vars.phi = 0.0;
	}
	return *this;
}

coord & coord::operator += (const coordSphere &b)		{	
	double sinPhi = sin(b.vars.phi);
	vars.x += b.vars.radius * cos(b.vars.theta) * sinPhi;
	vars.y += b.vars.radius * sin(b.vars.theta) * sinPhi;
	vars.z += b.vars.radius * cos(b.vars.phi);
	Round(vars.x);
	Round(vars.y);
	Round(vars.z);
	return *this;
}

coord & coord::operator -= (const coordSphere &b)		{	
	double sinPhi = sin(b.vars.phi);
	vars.x -= b.vars.radius * cos(b.vars.theta) * sinPhi;
	vars.y -= b.vars.radius * sin(b.vars.theta) * sinPhi;
	vars.z -= b.vars.radius * cos(b.vars.phi);
	Round(vars.x);
	Round(vars.y);
	Round(vars.z);
	return *this;
}
