#ifndef InputTZextBox_h
#define InputTZextBox_h

#include "TextHandler.h"

class CInputTextBox
{

public:

	//initialize inputextbox sets its position font and font size
	void Init(CLog *TLog, SDL_Rect Pos, std::string FontPath, SDL_Renderer *Render,SDL_Color Color, unsigned int Size = 0);

	//text input function
	int Input(SDL_Event *e);

	//Activity
	void ChangeActiv(bool Activation);
	bool IsActive();

	//returns contained text
	std::string GetText();

	//clears text
	void ClrTxt();

	//hiding text
	void Hide(bool Hid);

	//sets new text
	void SetTxt(std::string SetTxt);

	//chcange font color
	void ChangeColor(SDL_Color textCol);

	//render input box and text on it
	void Render();

private:

	//pointer to log file
	CLog *Log;

	//pointer to renderer
	SDL_Renderer *Renderer;

	//position
	SDL_Rect RPos;

	//current text
	std::string Txt;

	//font color
	SDL_Color TextColor;

	//class for display text
	CTextHandler TxtOnScreen;

	//need to input
	bool BInput;

	//true when need hide text on screen
	bool BHide;

	//font size
	unsigned int TxtSize;
};

#endif