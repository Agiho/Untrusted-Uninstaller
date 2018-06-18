#ifndef Texture_h
#define Texture_h

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include "Log.h"

class CTexture
{

public:

	//Initializes object by defoult values
	CTexture();

	//Deallocates memory
	~CTexture();

	//Initialize values
	void Init(SDL_Renderer* Render, CLog* LogT);

	//Deallocates memory
	void Free();

	//Load image to texture from file
	bool Load(std::string Path);

	//Renders texture with given values
	void Render(int x = 0, int y = 0, SDL_Rect* clip = NULL, int NeW = NULL, int NeWH = NULL, double angle = 0.0, SDL_Point* center = NULL, 
		SDL_RendererFlip flip = SDL_FLIP_NONE); 

	//Set blend mode
	void SetBlendMode( SDL_BlendMode blending );

	//Set alpha 
	void SetAlpha( Uint8 alpha );

	//return image diamensions
	int GetWidth();
	int GetHeight();

	//resize options
	void Resize(int NewW, int NewH);

	//return path to texture
	std::string GetPath();
	
private:

	// Log file
	CLog *Log;

	//is this object resized
	bool BResized;

	//Image diamensions
	int Width,Height;

	//Keeps Texture
	SDL_Texture* Texture;

	//Pointer to Renderer
	SDL_Renderer* Renderer;

	std::string STexPath;
};

#endif