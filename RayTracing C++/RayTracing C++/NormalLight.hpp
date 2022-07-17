#ifndef NORMALLIGHT_H
#define NORMALLIGHT_H

#include <memory>
#include "Vector.h"
#include "ray.hpp"
#include "NormalObj.hpp"

namespace RTracing
{
	class NormalLight
	{
	public:
		// Constructor / destructor.
		NormalLight();
		virtual ~NormalLight();

		// Function to compute illumination contribution.
		virtual bool ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal,
			const std::vector<std::shared_ptr<RTracing::NormalObj>>& objectList,
			const std::shared_ptr<RTracing::NormalObj>& currentObject,
			Vector<double>& color, double& intensity);

	public:
		Vector<double>	m_color{ 3 };
		Vector<double>	m_location{ 3 };
		double	m_intensity;
	};
}

#endif