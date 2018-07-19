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

	// initialize window with input boxes and button
	void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect Posbyttex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font);

	//render window
	void Render();

	//input handling, returns true when login button is pressed
	bool HandleEvent(SDL_Event *e);

	// returns info contained in boxes
	std::string GetIP();
	std::string GetUser();
	std::string GetPassword();

private:

	CLog * Log;

	SDL_Renderer *Renderer;

	//Descriptions
	CTextHandler IPDescrip;
	CTextHandler UserDescrip;
	CTextHandler PassDescrip;

	//input textbox
	CInputTextBox IP;
	CInputTextBox User;
	CInputTextBox Password;

	SDL_Rect Window;

	CButton LogIn;
};

#endif