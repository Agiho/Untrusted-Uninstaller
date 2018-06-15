#ifndef TemplateCheckBoxCont_h
#define TemplateCheckBoxCont_h

#include <SDL.h>
#include <memory>
#include <vector>
#include "Texture.h"
#include "UinstPrgCont.h"
#include "TextHandler.h"
#include "Slider.h"

template <class T>
class CCheckBoxCont
{

public:

	void Init(CLog *TLog, SDL_Rect Pos, unsigned int SliderSize, unsigned int WinW, unsigned int WintH, SDL_Renderer *Renderer, std::vector<T> *WhatContains, std::string FontPath, std::shared_ptr<CTexture> SliderTex);

	void Render();

	void HandleEvent(SDL_Event *e);

	std::vector<T> GetChk();

	void SetNewList(std::vector<T> *PNewrg);

	unsigned int Checked();

	std::vector<T>* GetAll();

	void AddNewOne(T New);

private:

	CLog * Log;
	SDL_Renderer *Renderer;

	unsigned int INrChecked;

	unsigned int CurrentLine;

	unsigned int WinWidth, WinHeight; //Window size

	std::vector<SDL_Rect> Sqrs; //checkbox size and position

	SDL_Rect Frame; //main frame of this object 

	CSlider Slider;

	std::vector<CTextHandler> Names;

	std::vector<T> *Content; //program and uninstall paths list

};


template <class T>
void CCheckBoxCont<T>::Init(CLog *TLog, SDL_Rect Pos, unsigned int SliderSize, unsigned int WinW, unsigned int WintH, SDL_Renderer *Render, std::vector<T> *WhatContains, std::string FontPath, std::shared_ptr<CTexture> SliderTex)
{
	Log = TLog;
	Renderer = Render;
	Content = WhatContains;

	//filled rectangle
	Frame = Pos;

	int i = 0;
	bool Exit = false;
	while (!Exit)
	{
		// filled rectangle 
		SDL_Rect fillRect = { (Frame.x + 10), (Frame.y + 10) + (i * 40), 20, 20 };
		Sqrs.push_back(fillRect);
		SDL_Point NamePoint = { (fillRect.x + 2 * fillRect.w - 2), fillRect.y };
		CTextHandler Name;
		Name.Init(NamePoint, FontPath, fillRect.h - 6, TLog, Render);
		Names.push_back(Name);

		// if boxex reach end of main container box end loop; 
		if (((Frame.y + 10) + ((i + 1) * 40) + 20) > (Frame.y + Frame.h)) Exit = true;
		++i;
	}

	CurrentLine = 0;

	Slider.Init(TLog, (Frame.x + Frame.w), Frame.y, SliderSize, Frame.h, SliderSize, SliderSize, SliderSize, SliderSize, SliderTex, 0, 0, Render);
	Slider.ChangeVis(true);
	Slider.SetMaxVal((*Content).size() - Names.size());

	//checking how many is already checked
	INrChecked = 0;
	if(!((*Content).empty()))
	{
		for(int i = 0; i < (*Content).size(); ++i)
		{
			if((*Content)[i].BChecked) ++INrChecked;
		}
	}
}

template <class T>
void CCheckBoxCont<T>::Render()
{

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
	SDL_RenderFillRect(Renderer, &Frame); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF); //black
	SDL_RenderDrawRect(Renderer, &Frame); //border

	int i = CurrentLine;
	
	if(!((*Content).empty()))
	{
		for (int SqrI = 0; SqrI < Sqrs.size(); ++SqrI)
		{
			if(i < (*Content).size())
			{
				if((*Content)[i].BChecked)
				{
					SDL_SetRenderDrawColor(Renderer, 0xFF, 0x00, 0x00, 0xFF); // red
					SDL_RenderFillRect(Renderer, &Sqrs[SqrI]); //render filled rect
				}
				else
				{
					SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
					SDL_RenderFillRect(Renderer, &Sqrs[SqrI]); //render filled rect
				}

				SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF); //black
				SDL_RenderDrawRect(Renderer, &Sqrs[SqrI]); //border

														   //render program name
				SDL_Color Col = { 0,0,0 };
				Names[SqrI].LoadFromRenderedText((*Content)[i].Name, Col);
				Names[SqrI].Render();
			}
			++i;
		}
	}
	Slider.Render();
}

template <class T>
void CCheckBoxCont<T>::HandleEvent(SDL_Event *e)
{
	//slider handle
	Slider.HandleEvent(e);
	CurrentLine = Slider.GetCurValue();

	//Checkbox Events  

	//If mouse event happened
	for (int i = 0; i < Sqrs.size(); ++i)
	{
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
		{
			//Get mause position
			int X, Y;
			SDL_GetMouseState(&X, &Y);

			//Check if mouse is inside checkbox
			bool BInside = true;
			//Mouse is left of the checkbox
			if (X < Sqrs[i].x)
			{
				BInside = false;
			}
			//Mouse is right of the checkbox
			else if (X > Sqrs[i].x + Sqrs[i].w)
			{
				BInside = false;
			}
			//Mouse above the checkbox
			else if (Y < Sqrs[i].y)
			{
				BInside = false;
			}
			//Mouse below the checkbox
			else if (Y > Sqrs[i].y + Sqrs[i].h)
			{
				BInside = false;
			}
			//Mouse is outside checkbox
			if (!BInside)
			{

			}
			//Mouse is inside checkbox
			else
			{
				//Set mouse over sprite
				switch (e->type)
				{
					// When mouse is on checkbox
				case SDL_MOUSEMOTION:
					break;
					++INrChecked;
					//When button is checkbox
				case SDL_MOUSEBUTTONDOWN:

					if(CurrentLine + i < (*Content).size())
					{
						if((*Content)[CurrentLine + i].BChecked)
						{
							(*Content)[CurrentLine + i].BChecked = false;
							if(INrChecked)--INrChecked;
						}
						else 
						{
							(*Content)[CurrentLine + i].BChecked = true;
							++INrChecked;
						}
					}
					break;

				}
			}
		}

	}
}

template <class T>
std::vector<T> CCheckBoxCont<T>::GetChk()
{
	std::vector<T> Return;
	for (int i = 0; i < (*Content).size(); ++i)
	{
		if ((*Content)[i].BChecked) Return.push_back(((*Content)[i]));
	}
	return Return;
}

template <class T>
void CCheckBoxCont<T>::SetNewList(std::vector<T> *New)
{
	Content = New;
	Slider.SetMaxVal((*Content).size() - Names.size());
}

template <class T>
unsigned int CCheckBoxCont<T>::Checked()
{
	return INrChecked;
}

template <class T>
std::vector<T>* CCheckBoxCont<T>::GetAll()
{
	return Content;
}

template <class T>
void CCheckBoxCont<T>::AddNewOne(T New)
{
	(*Content).push_back(New);
}


#endif