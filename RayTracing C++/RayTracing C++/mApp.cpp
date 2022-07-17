#include "mApp.h"
#include "Vector.h"
// constructor
mApp::mApp()
{
	isRunning = true;
	SDLWindow = NULL;
	SDLRenderer = NULL;
}

//initialization of SDL2
bool mApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	SDLWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	if (SDLWindow != NULL)
	{
		// Init renderer
		SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, 0);

		// Init Image instance
		m_image.Initialize(1280, 720, SDLRenderer);

		// Set the background color to white.
		SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);
		SDL_RenderClear(SDLRenderer);

		// Render the scene.
		m_scene.Render(m_image);

		// Display the image.
		m_image.Display();

		// Show the result.
		SDL_RenderPresent(SDLRenderer);

	}
	else
	{
		return false;
	}

	return true;
}

//set up of SDL2
int mApp::OnExecute()
{
	SDL_Event event;

	if (OnInit() == false)
	{
		return -1;
	}
	

	//until they are events, it will show the render
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}

		OnLoop();
		OnRender();
	}

	OnExit();
	return 0;
}


void mApp::OnLoop()
{

}

void mApp::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void mApp::OnRender()
{

}

void mApp::OnExit()
{
	//screenshot png
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, 1280, 720, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(SDLRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	SDL_SaveBMP(sshot, "screenshot.png");
	SDL_FreeSurface(sshot);

	//SDL2 for quit
	SDL_DestroyRenderer(SDLRenderer);
	SDL_DestroyWindow(SDLWindow);
	SDLWindow = NULL;
	SDL_Quit();
}

void mApp::PrintVector(const Vector<double>& inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}

