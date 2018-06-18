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


std::wstring UTF8toUnicode(const std::string& s)
{
    std::wstring ws;
    wchar_t wc;
    for( int i = 0;i < s.length(); )
    {
        char c = s[i];
        if ( (c & 0x80) == 0 )
        {
            wc = c;
            ++i;
        }
        else if ( (c & 0xE0) == 0xC0 )
        {
            wc = (s[i] & 0x1F) << 6;
            wc |= (s[i+1] & 0x3F);
            i += 2;
        }
        else if ( (c & 0xF0) == 0xE0 )
        {
            wc = (s[i] & 0xF) << 12;
            wc |= (s[i+1] & 0x3F) << 6;
            wc |= (s[i+2] & 0x3F);
            i += 3;
        }
        else if ( (c & 0xF8) == 0xF0 )
        {
            wc = (s[i] & 0x7) << 18;
            wc |= (s[i+1] & 0x3F) << 12;
            wc |= (s[i+2] & 0x3F) << 6;
            wc |= (s[i+3] & 0x3F);
            i += 4;
        }
        else if ( (c & 0xFC) == 0xF8 )
        {
            wc = (s[i] & 0x3) << 24;
            wc |= (s[i] & 0x3F) << 18;
            wc |= (s[i] & 0x3F) << 12;
            wc |= (s[i] & 0x3F) << 6;
            wc |= (s[i] & 0x3F);
            i += 5;
        }
        else if ( (c & 0xFE) == 0xFC )
        {
            wc = (s[i] & 0x1) << 30;
            wc |= (s[i] & 0x3F) << 24;
            wc |= (s[i] & 0x3F) << 18;
            wc |= (s[i] & 0x3F) << 12;
            wc |= (s[i] & 0x3F) << 6;
            wc |= (s[i] & 0x3F);
            i += 6;
        }
        ws += wc;
    }
    return ws;
}

bool CTextHandler::LoadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	Free();
    

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

bool CTextHandler::LoadFromRenderedTextUnicode( std::wstring textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	Free();
	
//TTF_RenderText_Solid
	
	SDL_Surface* textSurface = TTF_RenderUNICODE_Solid( gFont, (const Uint16*)(textureText.c_str()), textColor );
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