#include "TextHandler.h"


CTextHandler::CTextHandler()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	gFont = NULL;
}

CTextHandler::~CTextHandler()
{
	//Deallocate
	Free();
}

void CTextHandler::Init(SDL_Point TPos, std::string Path, unsigned int Size, CLog *TLog, SDL_Renderer *Render)
{
	Log = TLog;
	Renderer = Render;

	Pos = TPos;

	//Open the font
	gFont = TTF_OpenFont(Path.c_str(), Size);
	if (gFont == NULL)
	{
		std::stringstream stream;
		stream << "Failed to load font! SDL_ttf Error: %s\n"  <<  TTF_GetError();
		Log->WriteTxt(stream.str());
		
	}
}

void CTextHandler::SetPos(SDL_Point Point )
{
	Pos = Point;
}
bool CTextHandler::LoadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	Free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		std::stringstream stream;
		stream << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError();
		Log->WriteTxt(stream.str());
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( Renderer, textSurface );
		if( mTexture == NULL )
		{
			std::stringstream stream;
			stream << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError();
			Log->WriteTxt(stream.str());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}

void CTextHandler::Free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void CTextHandler::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void CTextHandler::SetBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void CTextHandler::SetAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void CTextHandler::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	if(x == (-1))
	{
		x = Pos.x;
		y = Pos.y;
	}
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( Renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int CTextHandler::GetWidth()
{
	return mWidth;
}

int CTextHandler::GetHeight()
{
	return mHeight;
}