#include "NormalObj.hpp"
#include <math.h>

#define EPSILON 1e-21f;

// Default constructor.
RTracing::NormalObj::NormalObj()
{

}

// The destructor.
RTracing::NormalObj::~NormalObj()
{

}

// Function to test for intersections.
bool RTracing::NormalObj::TestIntersection(const Ray& castRay, Vector<double>& intPoint, Vector<double>& localNormal, Vector<double>& localColor)
{
	return false;
}

// Function to test whether two floating-point numbers are close to being equal.
bool RTracing::NormalObj::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}