#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "NormalLight.hpp"

namespace RTracing
{
	class PointLight : public NormalLight
	{
	public:
		// The default constructor
		PointLight();

		// Override the default destructor
		virtual ~PointLight() override;

		// Function to compute illumination
		virtual bool ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal,
			const std::vector<std::shared_ptr<RTracing::NormalObj>>& objectList,
			const std::shared_ptr<RTracing::NormalObj>& currentObject,
			Vector<double>& color, double& intensity) override;
	};
}

#endif