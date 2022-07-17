#ifndef NORMALOBJ_H
#define NORMALOBJ_H

#include "Vector.h"
#include "Ray.hpp"

namespace RTracing
{
	class NormalObj
	{
		public:
		// Constructor and destructor.
		NormalObj();
		virtual ~NormalObj();

		// Function to test for intersections.
		virtual bool TestIntersection(const Ray& castRay, 
			Vector<double>& intPoint, Vector<double>& localNormal,
			Vector<double>& localColor);

		// Function to test whether two floating-point numbers are close to being equal.
		bool CloseEnough(const double f1, const double f2);

		// Public member variables.
	public:
		// The base colour of the object.
		Vector<double> m_baseColor{ 3 };
	};
}

#endif