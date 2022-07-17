#include "PointLight.hpp"

// Default constructor.
RTracing::PointLight::PointLight()
{
	m_color = Vector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	m_intensity = 1.0;
}

// Destructor.
RTracing::PointLight::~PointLight()
{

}

// Function to compute illumination.
bool RTracing::PointLight::ComputeIllumination(const Vector<double>& intPoint, const Vector<double>& localNormal,
	const std::vector<std::shared_ptr<RTracing::NormalObj>>& objectList,
	const std::shared_ptr<RTracing::NormalObj>& currentObject,
	Vector<double>& color, double& intensity)
{
	// Construct a vector pointing from the intersection point to the light.
	Vector<double> lightDir = (m_location - intPoint).Normalized();

	// Compute a starting point.
	Vector<double> startPoint = intPoint;

	// Compute the angle between the local normal and the light ray.
	// Note that we assume that localNormal is a unit vector.
	double angle = acos(Vector<double>::dot(localNormal, lightDir));

	// If the normal is pointing away from the light, then we have no illumination.
	if (angle > 1.5708)
	{
		// No illumination.
		color = m_color;
		intensity = 0.0;
		return false;
	}
	else
	{
		// We do have illumination.
		color = m_color;
		intensity = m_intensity * (1.0 - (angle / 1.5708));
		//intensity = 1.0;
		return true;
	}

	return true;
}