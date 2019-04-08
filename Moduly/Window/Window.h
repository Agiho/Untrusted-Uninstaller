#ifndef Window_h
#define Window_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include "Log.h"

class CWindow
{

public:

	// Initialize variables by defoult
	CWindow(std::string WTitle, CLog* LogT,int SCRW = 1024, int SCRH = 768, Uint32 Type = SDL_WINDOW_FULLSCREEN, std::string IconPathT = "");

	// Deallocate memory
	~CWindow();

	// initialize Window
	bool Init();

	//Clear and Close Window
	void Close();

	// Clear screen
	void ClearScr(Uint8 r , Uint8 g , Uint8 b , Uint8 a );

	//Update screen
	void UpdateScr();

	// Returns pointer to Renderer
	SDL_Renderer* GetRenderer();

private:

	//The window we'll be rendering to
	SDL_Window* Window;

	//The window renderer
	SDL_Renderer* Renderer;
	
	//Window diamensions
	int ScrWidth;
	int ScrHeight;
	Uint32 WType;
	std::string Title;
	std::string IconPath;
	CLog* Log;

};

#endif