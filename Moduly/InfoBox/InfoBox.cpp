#include "InfoBox.h"

void CInfoBox::Init(CLog *TLog, SDL_Rect TSize, SDL_Renderer *Render, std::string TFont, SDL_Color NewCol)
{
	Log = TLog;
	Size = TSize;
	Renderer = Render;

	CurText = "";
	CurWText = L"NoInfo";

	Font = TFont;

	Col = NewCol;

	TxtSize = 15;

	SDL_Point PPos = {TSize.x + 5, TSize.y + ((TSize.h/2) - TxtSize/2)};
	TxtPos = PPos;
	Info.Init(PPos,Font, 15, TLog, Render);
	Info.LoadFromRenderedTextUnicode(CurWText, Col);
}

void CInfoBox::SetInfo(std::string Txt)
{
	CurText = Txt;

	Info.LoadFromRenderedText(CurText, Col);

	TxtPos.x = Size.x + Size.w/2 - Info.GetWidth()/2;
}

void CInfoBox::SetInfo(std::wstring Txt)
{
	CurWText = Txt;

	Info.LoadFromRenderedTextUnicode(CurWText, Col);

	TxtPos.x = Size.x + Size.w/2 - Info.GetWidth()/2;
}

std::string CInfoBox::GetCurText()
{
	return CurText;
}
std::wstring CInfoBox::GetCurText(bool B)
{
	return CurWText;
}

void CInfoBox::ChangeSize(SDL_Rect NewSize)
{
	Size = NewSize;

	TxtPos.y = Size.y + ((Size.h/2) - TxtSize/2);
}

SDL_Rect CInfoBox::GetSize()
{
	return Size;
}

void CInfoBox::ChangeTxtSize(unsigned int NewSize)
{
	TxtSize = NewSize;
}

void CInfoBox::ChangeTxtCol(SDL_Color NewCol)
{
	Col = NewCol;
}

void CInfoBox::Render()
{
	//Box
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // color
	SDL_RenderFillRect(Renderer, &Size); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Size); //border

	//texts
	Info.Render(TxtPos.x, TxtPos.y);
}