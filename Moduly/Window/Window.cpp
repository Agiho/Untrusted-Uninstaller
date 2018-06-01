#include "Window.h"

CWindow::CWindow(std::string WTitle, CLog* LogT, int SCRW ,int SCRH, Uint32 Type  )
{
	//The window we'll be rendering to
	Window = NULL;

	//The window renderer
	Renderer = NULL;

	ScrWidth = SCRW;
	ScrHeight = SCRH;
	WType = Type;
	Title =WTitle;
	LogT = Log;
}

CWindow::~CWindow()
{
	Close();
}

// initialize window renderer and image loading
bool CWindow::Init()
{
	// variable for stream and string to get throw
	std::stringstream Stream;
	Stream.str("");
	std::string SErrString;
	//Succes flag
	bool Ok = true;

	try
	{
		// Initialize SDL
		//Initialize SDL_ttf
		if (TTF_Init() == -1)
		{
		Stream <<"SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << "\n";
		SErrString = Stream.str();
		throw SErrString;
		}
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0 )
		{
			//wxception
			Stream << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError() << "\n";
			SErrString = Stream.str();
			throw SErrString;
		}
		else
		{
			//Set filtering to linear
				if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
				{
					//wxception
					Stream << "Warning: Linear texture filtering not enabled! \n";
					SErrString = Stream.str();
					throw SErrString;
				}
				//Create Window 
				Window = SDL_CreateWindow(Title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, ScrWidth, ScrHeight, WType);
				if(Window == NULL)
				{
					//wxception
					Stream << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << "\n";
					SErrString = Stream.str();
					throw SErrString;
				}
				else
				{
					Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
					if(Renderer == NULL)
					{
						//wxception
						Stream << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << "\n";
						SErrString = Stream.str();
						throw SErrString;
					}
					else
					{
						//Initialize Renderer color
						SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

						//Initialize image loading
						int Img = IMG_INIT_PNG;
						if(!(IMG_Init(Img) & Img ) )
						{
							//wxception
							Stream << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << "\n" ;
							SErrString = Stream.str();
							throw SErrString;
						}
					}
				}
		}
	}
	catch(std::string Error)
	{
		Log->WriteTxt(Error);
	}
	return Ok;
}

//Clear and close
void CWindow::Close()
{
	//Destroy Window and renderer
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Renderer = NULL;
	Window = NULL;

	//quit SDL_Mixer, SDL_image loading and SDL
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

//Clear screen
void CWindow::ClearScr(Uint8 r = 0xff, Uint8 g = 0xff, Uint8 b = 0xff, Uint8 a = 0xff)
{
	// Set bg color and clear
	SDL_SetRenderDrawColor( Renderer, r, g, b, a );
	SDL_RenderClear(Renderer);
}

//Update screen
void CWindow::UpdateScr()
{
	SDL_RenderPresent(Renderer);
}

//Returning pointer to Renderer
SDL_Renderer* CWindow::GetRenderer()
{
	return Renderer;
}