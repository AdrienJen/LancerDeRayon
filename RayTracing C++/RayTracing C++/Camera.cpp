#include "Camera.hpp"
#include "Ray.hpp"
#include "math.h"

RTracing::Camera::Camera()
{
	// The default constructor.
	m_cameraPosition = Vector<double>{ std::vector<double> {0.0, -10.0, 0.0} };
	m_cameraLookAt = Vector<double>{ std::vector<double> {0.0, 0.0, 0.0} };
	m_cameraUp = Vector<double>{ std::vector<double> {0.0, 0.0, 1.0} };
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

void RTracing::Camera::SetPosition(const Vector<double>& newPosition)
{
	m_cameraPosition = newPosition;
}

void RTracing::Camera::SetLookAt(const Vector<double>& newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void RTracing::Camera::SetUp(const Vector<double>& upVector)
{
	m_cameraUp = upVector;
}

void RTracing::Camera::SetLength(double newLength)
{
	m_cameraLength = newLength;
}

void RTracing::Camera::SetHorzSize(double newHorzSize)
{
	m_cameraHorzSize = newHorzSize;
}

void RTracing::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}

// Method to return the position of the camera
Vector<double> RTracing::Camera::GetPosition()
{
	return m_cameraPosition;
}

// Method to return the look at of the camera
Vector<double> RTracing::Camera::GetLookAt()
{
	return m_cameraLookAt;
}

// Method to return the up vector of the camera
Vector<double> RTracing::Camera::GetUp()
{
	return m_cameraUp;
}

// Method to return the length of the camera
double RTracing::Camera::GetLength()
{
	return m_cameraLength;
}

double RTracing::Camera::GetHorzSize()
{
	return m_cameraHorzSize;
}

double RTracing::Camera::GetAspect()
{
	return m_cameraAspectRatio;
}

Vector<double> RTracing::Camera::GetU()
{
	return m_projectionScreenU;
}

Vector<double> RTracing::Camera::GetV()
{
	return m_projectionScreenV;
}

Vector<double> RTracing::Camera::GetScreenCentre()
{
	return m_projectionScreenCentre;
}

void RTracing::Camera::UpdateCameraGeometry()
{
	// compute the vector from the camera position to the LookAt position
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();

	//compute the alpha and beta unit vectors
	m_projectionScreenU = Vector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = Vector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();

	//compute the position of the center point of the screen
	m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

	// Modify the U and V vectors to match the size and aspect ratio.
	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool RTracing::Camera::GenerateRay(float ScreenX, float ScreenY, RTracing::Ray& cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	Vector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * ScreenX);
	Vector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * ScreenY);

	// Use this point along with the camera position to compute the ray
	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
	return true;
}
