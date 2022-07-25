#ifndef MAPP_H
#define MAPP_H

#include <SDL.h>
#include "Image.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

class mApp
{
	public:
	mApp();

	int OnExecute();
	bool OnInit();
	void OnLoop();
	void OnEvent(SDL_Event* event);
	void OnRender();
	void OnExit();

private:
	//Debug display vector to terminal
	void PrintVector(const Vector<double>& inputVector);

	Image m_image;

	RTracing::Scene m_scene;
	// SDL2 for running
	bool isRunning;
	SDL_Window* SDLWindow;
	SDL_Renderer* SDLRenderer;

};

#endif