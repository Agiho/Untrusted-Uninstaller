#ifndef InfoBox_h
#define InfoBox_h

#include "TextHandler.h"

class CInfoBox
{
public:

	//creates InfoBox
	void Init(CLog *TLog, SDL_Rect TSize, SDL_Renderer *Render, std::string TFont, SDL_Color NewCol);

	// sets text to render
	void SetInfo(std::string Txt);
	void SetInfo(std::wstring Txt);

	// returns text which is inside infobox
	std::string GetCurText();
	std::wstring GetCurText(bool B);

	//change box size
	void ChangeSize(SDL_Rect NewSize);

	//returns box size
	SDL_Rect GetSize();

	// change text size
	void ChangeTxtSize(unsigned int NewSize);

	// change ext color
	void ChangeTxtCol(SDL_Color NewCol);

	//render box and text
	void Render();

private:

	CLog *Log; 

	SDL_Renderer *Renderer;

	std::string Font; //path to file with font

	SDL_Color Col; //color

	unsigned int TxtSize; //text size

	SDL_Point TxtPos; //where start draw text

	SDL_Rect Size; // box size

	CTextHandler Info; //object for rendering text

	std::string CurText;//text to render
	std::wstring CurWText;//text to render
};

#endif