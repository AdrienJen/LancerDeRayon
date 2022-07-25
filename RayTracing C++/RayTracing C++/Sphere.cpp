#include "Sphere.hpp"
#include <cmath>


RTracing::Sphere::Sphere()
{

}

RTracing::Sphere::~Sphere()
{

}

// Function to test for intersections
bool RTracing::Sphere::TestIntersection(const RTracing::Ray& castRay,
	Vector<double>& intPoint,
	Vector<double>& localNormal,
	Vector<double>& localColor)
{
	// Compute the values of a, b and c
	Vector<double> vhat = castRay.m_lab;
	vhat.Normalize();

		// a = 1.0;

		// Calculate b.
	double b = 2.0 * Vector<double>::dot(castRay.m_point1, vhat);

	// Calculate c.
	double c = Vector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

	// if we actually have an intersection
	double intTest = (b * b) - 4.0 * c;

	if (intTest > 0.0)
	{
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;

		// If behind the camera, ignore it
		if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
		else
		{
			// Determine which point of intersection was close to camera
			if (t1 < t2)
			{
				intPoint = castRay.m_point1 + (vhat * t1);
			}
			else
			{
				intPoint = castRay.m_point1 + (vhat * t2);
			}
			// Compute the local normal
			localNormal = intPoint;
			localNormal.Normalize();
		}

		return true;
	}
	else
	{
		return false;
	}

}