#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL.h>
#include "Image.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include <memory>
#include "PointLight.hpp"

namespace RTracing
{
	class Scene
	{
		
	public:
		
		Scene();

		bool Render(Image& outputImage);

		
	private:
		// The camera that we will use
		RTracing::Camera m_camera;

		// The list of objects in the scene
		std::vector<std::shared_ptr<RTracing::NormalObj>> m_objectList;


			// The list of lights in the scene
		std::vector<std::shared_ptr<RTracing::NormalLight>> m_lightList;

	};
}

#endif