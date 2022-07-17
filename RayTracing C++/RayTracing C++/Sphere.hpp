#ifndef SPHERE_H
#define SPHERE_H

#include "NormalObj.hpp"

namespace RTracing
{
	class Sphere : public NormalObj
	{
		//constructor
	public:
		
		Sphere();

		// Override the destructor.
		virtual ~Sphere() override;

		// Override the function to test for intersections.
		virtual bool TestIntersection(const RTracing::Ray& castRay,
			Vector<double>& intPoint,
			Vector<double>& localNormal,
			Vector<double>& localColor);

	private:


	};
}

#endif