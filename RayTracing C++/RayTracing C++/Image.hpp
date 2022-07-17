
#ifndef IMAGE_H
#define IMAGE_H



#include <SDL.h>
#include <vector>
// Image class for 2d image
class Image
{
public:
	// Constructor
	Image();

	// Destructor
	~Image();

	// Initialize
	void Initialize(const int xSize, const int ySize, SDL_Renderer* SDLRenderer);

	// Set pixels
	void SetPixel(const int x, const int y, const double r, const double g, const double b);

	//dimensions of the image
	int GetXSize();
	int GetYSize();

	// Display
	void Display();

private:
	Uint32 ConvertColor(const double r, const double g, const double b);
	void InitTexture();

private:
	//Store image data in array
	std::vector<std::vector<double>> rChannel;
	std::vector<std::vector<double>> gChannel;
	std::vector<std::vector<double>> bChannel;

	//Store size of the image
	int m_xSize, m_ySize;

	
	SDL_Renderer* SDLRenderer;
	SDL_Texture* SDLTexture;

};

#endif