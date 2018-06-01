#ifndef UserAndIP_h
#define UserAndIP_h

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Texture.h"
#include "Button.h"
#include "InputTextBox.h"

class CUserAndIP 
{

public:

	void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect TexPos,
		unsigned int SCrW,  unsigned int SCrH, SDL_Rect ButSize);

	void Render();

	bool HandleEvent(SDL_Event *e);

private:


	//textbox
	CInputTextBox IP;
	CInputTextBox User;
	CInputTextBox Password;

	CButton LogIn;

	std::shared_ptr<CTexture> Texture; 


};

#endif