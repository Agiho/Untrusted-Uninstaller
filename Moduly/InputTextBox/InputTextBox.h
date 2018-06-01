#ifndef InputTZextBox_h
#define InputTZextBox_h

#include "TextHandler.h"

class CInputTextBox
{

public:

	void Init(CLog *TLog, SDL_Rect Pos, std::string FontPath, SDL_Renderer *Render,SDL_Color Color, unsigned int Size = 0);

	void Input(SDL_Event *e);

	std::string GetText();

	void ClrTxt();
	void SetTxt(std::string SetTxt);

	void ChangeColor(SDL_Color textCol);

	void Render();

private:

	CLog *Log;

	SDL_Renderer *Renderer;

	SDL_Rect RPos;

	std::string Txt;

	SDL_Color TextColor;

	CTextHandler TxtOnScreen;
};

#endif