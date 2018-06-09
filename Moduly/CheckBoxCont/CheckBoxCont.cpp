#include "CheckBoxCont.h"

void CCheckBoxCont::Init(CLog *TLog, SDL_Rect Pos, unsigned int WinW, unsigned int WintH, SDL_Renderer *Render, std::vector<CUinstPrgCont> *Programslst, std::string FontPath, std::shared_ptr<CTexture> SliderTex)
{
	Log = TLog;
	Renderer = Render;
	Programs = Programslst;

	Frame = Pos;

	//filled rectangle
	
	
	int i = 0;
	bool Exit = false;
	while(!Exit)
	{
		// filled rectangle 
		SDL_Rect fillRect = { (Frame.x + 10), (Frame.y + 10) + (i*40), 20, 20 }; 
		Sqrs.push_back(fillRect);
		SDL_Point NamePoint = {(fillRect.x +2*fillRect.w), fillRect.y};
		CTextHandler Name;
		Name.Init(NamePoint, FontPath, fillRect.h - 2, TLog, Render);
		Names.push_back(Name);

		// if boxex reach end of main container box end loop; 
		if(((Frame.y + 10) + ((i+1)*40) + 20) > (Frame.y + Frame.h)) Exit = true;
		++i;
	}
	
	CurrentLine = 0;

	Slider.Init(TLog, (Frame.x +Frame.w), Frame.y, 20, Frame.h, 50, 50, 50, 50, SliderTex,0,0, Render);
	Slider.ChangeVis(true);
	Slider.SetMaxVal((*Programs).size() - Names.size());

}

void CCheckBoxCont::Render()
{

	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF  ); // white
	SDL_RenderFillRect( Renderer, &Frame ); //render filled rect
	SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0xFF ); //black
	SDL_RenderDrawRect( Renderer, &Frame ); //border

	int i = CurrentLine;

	for(int SqrI = 0; SqrI < Sqrs.size(); ++SqrI)
	{

		if((*Programs)[i].BChecked)
		{
			SDL_SetRenderDrawColor( Renderer, 0xFF , 0x00, 0x00, 0xFF  ); // red
			SDL_RenderFillRect( Renderer, &Sqrs[SqrI] ); //render filled rect
		}
		else 
		{
			SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF  ); // white
			SDL_RenderFillRect( Renderer, &Sqrs[SqrI] ); //render filled rect
		}
		
		SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0xFF ); //black
		SDL_RenderDrawRect( Renderer, &Sqrs[SqrI] ); //border
	
		//render program name
		SDL_Color Col = {0,0,0};
		Names[SqrI].LoadFromRenderedText((*Programs)[i].Name, Col);
		Names[SqrI].Render();

		++i;
	}
	Slider.Render();
}

void CCheckBoxCont::HandleEvent(SDL_Event *e)
{
	//slider handle
	Slider.SetVal(CurrentLine);
	Slider.HandleEvent(e);
	CurrentLine = Slider.GetCurValue();

	//Checkbox Events  

	//If mouse event happened
	for(int i = 0; i < Sqrs.size(); ++i)
	{
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
		{
			//Get mause position
			int X, Y;
			SDL_GetMouseState(&X, &Y);

			//Check if mouse is inside checkbox
			bool BInside = true;
			//Mouse is left of the checkbox
			if( X < Sqrs[i].x )
			{
				BInside = false;
			}
			//Mouse is right of the checkbox
			else if( X > Sqrs[i].x + Sqrs[i].w )
			{
				BInside = false;
			}
			//Mouse above the checkbox
			else if( Y < Sqrs[i].y )
			{
				BInside = false;
			}
			//Mouse below the checkbox
			else if( Y > Sqrs[i].y + Sqrs[i].h )
			{
				BInside = false;
			}
			//Mouse is outside checkbox
			if( !BInside )
			{
				
			}
			//Mouse is inside checkbox
			else
			{
				//Set mouse over sprite
				switch( e->type )
				{
					// When mouse is on checkbox
					case SDL_MOUSEMOTION:
						break;
			
					//When button is checkbox
					case SDL_MOUSEBUTTONDOWN:

						(*Programs)[CurrentLine + i].BChecked = true;
						break;
				
				}
			}
		}

	}
}

std::vector<CUinstPrgCont> CCheckBoxCont::GetChkPrograms()
{
	std::vector<CUinstPrgCont> Return;
	for(int i = 0; i < (*Programs).size(); ++i)
	{
		if((*Programs)[i].BChecked) Return.push_back(((*Programs)[i]));
	}
	return Return;
}

void CCheckBoxCont::SetNewProgramList(std::vector<CUinstPrgCont> *Prg)
{
	Programs = Prg;
	Slider.SetMaxVal((*Programs).size() - Names.size());
}