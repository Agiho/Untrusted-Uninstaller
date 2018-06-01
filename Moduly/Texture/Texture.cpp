#include "Texture.h"

// Initialize variables by defoult
CTexture::CTexture()
{
	Width = 0;
	Height = 0;
	Texture = NULL;
	Log = nullptr;
}

// Deallocates memory
CTexture::~CTexture()
{
	Free();
	Log = nullptr;
}

//Initialize values
void CTexture::Init(SDL_Renderer* Render, CLog* LogT)
{
	Renderer = Render;
	Log = LogT;
}

//Deallocates memory
void CTexture::Free()
{
	//Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		Width = 0;
		Height = 0;
	}
}

//Load image to texture from file 
bool CTexture::Load(std::string Path)
{
	//Deallocates previous data
	Free();

	// Clear Texture
	SDL_Texture* Temptexture = NULL;

	//Load image from file to surface
	SDL_Surface* Surface = IMG_Load(Path.c_str());
	
	std::stringstream Stream;

		//if something went wrong
		if( Surface == NULL )
		{
		Stream << "Unable to load image ! SDL_image Error: \n" << Path.c_str() << IMG_GetError() << "\n";
		Log->WriteTxt(Stream.str());
		
		}
		else
		{
			//Color key image
			SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, 0, 0xff, 0xff));

			//Convert surface image to texture

			Temptexture = SDL_CreateTextureFromSurface(Renderer,Surface);

			//Checking loaded texture
			if( Temptexture == NULL )
			{
				Stream << "Unable to create texture from %s! SDL Error: %s\n" << Path.c_str() << SDL_GetError() << "\n" ;
				Log->WriteTxt(Stream.str());
			}
			else
			{
				//Set image dimensions
				Width = Surface->w;
				Height = Surface->h;
			}
			//Deallocate loaded Surface
			SDL_FreeSurface(Surface);

		}

	//Set actual Texture
	Texture = Temptexture;
	STexPath = Path;
	return Texture != NULL;
}

void CTexture::SetBlendMode(SDL_BlendMode blend)
{
	//Set blending
	SDL_SetTextureBlendMode( Texture, blend );
}
		
void CTexture::SetAlpha(Uint8 alpha)
{
	//Setting texture alpha
	SDL_SetTextureAlphaMod(Texture, alpha);
}

//Renders texture with given values
void CTexture::Render(int x, int y, SDL_Rect* Clip, double Angle, SDL_Point* Center, 
		SDL_RendererFlip Flip )
{
	//Rendering space
	SDL_Rect RQuad = {x, y , Width , Height};

	//checking if need piece of image to render
	if(Clip != NULL)
	{
		RQuad.w = Clip->w;
		RQuad.h = Clip->h;
	}
	//render image
	SDL_RenderCopyEx(Renderer, Texture, Clip, &RQuad, Angle, Center, Flip);
}

int CTexture::GetWidth()
{
	return Width;
}

int CTexture::GetHeight()
{
	return Height;
}

std::string CTexture::GetPath()
{
	return STexPath;
}