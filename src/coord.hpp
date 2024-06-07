#ifndef __COORD_HPP__
#define __COORD_HPP__

#include "typedefs.hpp"

#ifdef UNITTEST
#include <iostream>
#endif

union coord;
union coordSphere;
#define PRECISION 0.1

union coordSphere
{
	struct 
	{
		double						radius;		// Radius in meters; this allows for as many as 4 billion meters from center, that's plenty
		double						theta;		// = n * 360 / 65535
		double						phi;		// = n * 360 / 65535
	}								vars;
	
	UInt64						integer;

	inline bool operator < (const coordSphere &b) const		{	return (vars.radius == b.vars.radius ? (vars.theta == b.vars.theta ? (vars.phi < b.vars.phi ? true : false) : vars.theta < b.vars.theta) : vars.radius < b.vars.radius);	}
	inline bool operator > (const coordSphere &b) const		{	return (vars.radius == b.vars.radius ? (vars.theta == b.vars.theta ? (vars.phi > b.vars.phi ? true : false) : vars.theta > b.vars.theta) : vars.radius > b.vars.radius);	}
	inline bool operator == (const coordSphere &b) const	{	return (vars.radius - b.vars.radius) <= PRECISION && (vars.theta - b.vars.theta) <= PRECISION && (vars.phi - b.vars.phi) <= PRECISION;	}
	inline bool operator <= (const coordSphere &b) const	{	return (vars.radius == b.vars.radius ? (vars.theta == b.vars.theta ? (vars.phi <= b.vars.phi ? true : false) : vars.theta <= b.vars.theta) : vars.radius <= b.vars.radius);	}
	inline bool operator >= (const coordSphere &b) const	{	return (vars.radius == b.vars.radius ? (vars.theta == b.vars.theta ? (vars.phi >= b.vars.phi ? true : false) : vars.theta >= b.vars.theta) : vars.radius >= b.vars.radius);	}
	inline bool operator != (const coordSphere &b) const	{	return (vars.radius - b.vars.radius) > PRECISION || (vars.theta - b.vars.theta) > PRECISION || (vars.phi - b.vars.phi) > PRECISION;	}

	inline coordSphere &	operator = (const coordSphere &b)	{	vars.radius = b.vars.radius; vars.theta = b.vars.theta; vars.phi = b.vars.phi;	return *this;	}

	coordSphere & operator = (const coord &);
};

union coord
{
	struct
	{
		double						x;
		double						y;
		double						z;
	}							vars;
	double						axes[3];


	inline bool operator < (const coord &b)	const	{	return (vars.x == b.vars.x ? (vars.y == b.vars.y ? (vars.z < b.vars.z ? true : false) : vars.y < b.vars.y) : vars.x < b.vars.x);	}
	inline bool operator > (const coord &b)	const	{	return (vars.x == b.vars.x ? (vars.y == b.vars.y ? (vars.z > b.vars.z ? true : false) : vars.y > b.vars.y) : vars.x > b.vars.x);	}
	inline bool operator == (const coord &b) const	{	return ((vars.x - b.vars.x) <= PRECISION && (vars.y - b.vars.y) <= PRECISION && (vars.z - b.vars.z) <= PRECISION);	}
	inline bool operator <= (const coord &b) const	{	return (vars.x == b.vars.x ? (vars.y == b.vars.y ? (vars.z <= b.vars.z ? true : false) : vars.y <= b.vars.y) : vars.x <= b.vars.x);	}
	inline bool operator >= (const coord &b) const	{	return (vars.x == b.vars.x ? (vars.y == b.vars.y ? (vars.z >= b.vars.z ? true : false) : vars.y >= b.vars.y) : vars.x >= b.vars.x);	}
	inline bool operator != (const coord &b) const	{	return ((vars.x - b.vars.x) > PRECISION || (vars.y - b.vars.y) > PRECISION || (vars.z - b.vars.z) > PRECISION);	}

	inline coord &	operator = (const coord &b)	{	vars.x = b.vars.x; vars.y = b.vars.y; vars.z = b.vars.z;	return *this;	}

	inline coord & operator += (const coord &b)		{	
		vars.x += b.vars.x;
		vars.y += b.vars.y;
		vars.z += b.vars.z;
		return *this;
	}

	coord & operator += (const coordSphere &);

	inline coord & operator -= (const coord &b)		{	
		vars.x -= b.vars.x;
		vars.y -= b.vars.y;
		vars.z -= b.vars.z;
		return *this;
	}

	coord & operator -= (const coordSphere &b);
	// inline coord &	operator = (const coord &b)	{	vars.x = b.vars.x; vars.y = b.vars.y; vars.z = b.vars.z;	return *this;	}
	coord &	operator= (const coordSphere &);
};


#endif
