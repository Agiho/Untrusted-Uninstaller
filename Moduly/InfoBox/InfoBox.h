#ifndef InfoBox_h
#define InfoBox_h

#include "TextHandler.h"

class CInfoBox
{
public:

	void Init(CLog *TLog, SDL_Rect TSize, SDL_Renderer *Render, std::string TFont, SDL_Color NewCol);

	void SetInfo(std::string Txt);
	void SetInfo(std::wstring Txt);

	std::string GetCurText();
	std::wstring GetCurText(bool B);

	void ChangeSize(SDL_Rect NewSize);

	SDL_Rect GetSize();

	void ChangeTxtSize(unsigned int NewSize);

	void ChangeTxtCol(SDL_Color NewCol);

	void Render();

private:

	CLog *Log; 

	SDL_Renderer *Renderer;

	std::string Font;

	SDL_Color Col;

	unsigned int TxtSize;

	SDL_Point TxtPos;

	SDL_Rect Size;

	CTextHandler Info;

	std::string CurText;
	std::wstring CurWText;
};

#endif