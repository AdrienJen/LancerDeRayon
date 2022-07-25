#include "Scene.hpp"


RTracing::Scene::Scene()
{
	// Configure the camera
	m_camera.SetPosition(Vector<double>{std::vector<double> {0.0, -10.0, 0.0}});
	m_camera.SetLookAt(Vector<double>{std::vector<double> {0.0, 0.0, 0.0}});
	m_camera.SetUp(Vector<double>{std::vector<double> {0.0, 0.0, 1.0}});
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

	// Construct a  sphere
	m_objectList.push_back(std::make_shared<RTracing::Sphere>(RTracing::Sphere()));

	// Construct a light
	m_lightList.push_back(std::make_shared<RTracing::PointLight>(RTracing::PointLight()));
	m_lightList.at(0)->m_location = Vector<double>{ std::vector<double> {5.0, -10.0, -5.0} };
	m_lightList.at(0)->m_color = Vector<double>{ std::vector<double> {255.0, 255.0, 255.0} };
}

// Function to perform the renderering
bool RTracing::Scene::Render(Image& outputImage)
{
	// Get the dimensions of the output image
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	// Loop over each pixel in our image
	RTracing::Ray cameraRay;
	Vector<double> intPoint(3);
	Vector<double> localNormal(3);
	Vector<double> localColor(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int x = 0; x < xSize; ++x)
	{
		for (int y = 0; y < ySize; ++y)
		{
			// Normalize the x and y coordinates
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			// Generate the ray for this pixel
			m_camera.GenerateRay(normX, normY, cameraRay);

			// intersections with all objects in the scene
			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject->TestIntersection(cameraRay, intPoint, localNormal, localColor);

				// If we have a valid intersection, change pixel color 
				if (validInt)
				{
					// Compute intensity of illumination
					double intensity;
					Vector<double> color{ 3 };
					bool validIllum = false;
					for (auto currentLight : m_lightList)
					{
						validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
					}

					// Compute the distance between the camera and the point of intersection
					double dist = (intPoint - cameraRay.m_point1).norm();
					if (dist > maxDist)
						maxDist = dist;

					if (dist < minDist)
						minDist = dist;

					
					if (validIllum)
					{
						outputImage.SetPixel(x, y, 125*intensity , 70*intensity, 120*intensity);
					}
					else
					{
						outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
				else
				{
					outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
				}
			}
		}
	}



	return true;
}