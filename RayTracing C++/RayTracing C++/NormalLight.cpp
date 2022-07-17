
#include "NormalLight.hpp"

RTracing::NormalLight::NormalLight()
{

}

// Destructor.
RTracing::NormalLight::~NormalLight()
{

}

// Function to compute illumination.
bool RTracing::NormalLight::ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal,
	const std::vector<std::shared_ptr<RTracing::NormalObj>>& objectList,
	const std::shared_ptr<RTracing::NormalObj>& currentObject,
	Vector<double>& color, double& intensity)
{
	return false;
}