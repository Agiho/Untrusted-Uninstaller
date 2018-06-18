#ifndef TextHandler_h
#define TextHandler_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include "Log.h"
#include <vector>


class CTextHandler
{

public:

	//Initializes variables
	CTextHandler();

	//Deallocates memory
	~CTextHandler();

	void Init(SDL_Point TPos, std::string Path, unsigned int Size, CLog *TLog, SDL_Renderer *Render);

	//Loads image at specified path
	//bool loadFromFile(std::string path);

	void SetPos(SDL_Point Point);

	//Creates image from font string
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);
	bool LoadFromRenderedTextUnicode(std::wstring textureText, SDL_Color textColor);

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void SetBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(Uint8 alpha);

	//Renders texture at given point
	void Render(int x = (-1), int y = (-1), SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

private:

	//pointer to log
	CLog *Log;

	//The actual hardware texture
	SDL_Texture* mTexture;

	//Pointer to rednerer
	SDL_Renderer* Renderer;

	SDL_Point Pos;

	//Image dimensions
	int mWidth;
	int mHeight;

	//Globally used font
	TTF_Font *gFont;

};

#endif