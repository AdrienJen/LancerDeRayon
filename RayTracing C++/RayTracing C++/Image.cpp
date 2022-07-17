#include "Image.hpp"
#include <fstream>
// image class for 2d image

Image::Image()
{
	m_xSize = 0;
	m_ySize = 0;
	SDLTexture = NULL;
}

// The destructor.
Image::~Image()
{
	if (SDLTexture != NULL)
		SDL_DestroyTexture(SDLTexture);
}

// Function to initialize
void Image::Initialize(const int xSize, const int ySize, SDL_Renderer* Renderer)
{
	// Resize image data arrays
	rChannel.resize(xSize, std::vector<double>(ySize, 0));
	gChannel.resize(xSize, std::vector<double>(ySize, 0));
	bChannel.resize(xSize, std::vector<double>(ySize, 0));

	// Store dimensions.
	m_xSize = xSize;
	m_ySize = ySize;

	// Store pointer to renderer
	SDLRenderer = Renderer;

	// Initialise texture.
	InitTexture();
}

// Set pixels.
void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	rChannel.at(x).at(y) = red;
	gChannel.at(x).at(y) = green;
	bChannel.at(x).at(y) = blue;
}

//Display
void Image::Display()
{
	// Allocate memory for pixel buffer
	Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

	// Clear pixel buffer
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

	for (int x = 0; x < m_xSize; ++x)
	{
		for (int y = 0; y < m_ySize; ++y)
		{
			tempPixels[(y * m_xSize) + x] = ConvertColor(rChannel.at(x).at(y), gChannel.at(x).at(y), bChannel.at(x).at(y));
		}
	}

	// Update texture with pixel buffer
	SDL_UpdateTexture(SDLTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

	// Destroy pixel buffer
	delete[] tempPixels;

	// Copy texture to renderer
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 1280;
	srcRect.h = 720;
	bounds = srcRect;
	SDL_RenderCopy(SDLRenderer, SDLTexture, &srcRect, &bounds);
}

// Return image to a SDL2 texture
void Image::InitTexture()
{
	// Initialise the texture
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	// Delete any previously created texture
	if (SDLTexture != NULL)
		SDL_DestroyTexture(SDLTexture);

	// Create texture and store the image
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	SDLTexture = SDL_CreateTextureFromSurface(SDLRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}
// Functions to return the dimensions of the image.
int Image::GetXSize()
{
	return m_xSize;
}
int Image::GetYSize()
{
	return m_ySize;
}
// Convert color to Uint32
Uint32 Image::ConvertColor(const double red, const double green, const double blue)
{
	// Convert colours to unsigned char
	unsigned char r = static_cast<unsigned char>(red);
	unsigned char g = static_cast<unsigned char>(green);
	unsigned char b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

	return pixelColor;
}