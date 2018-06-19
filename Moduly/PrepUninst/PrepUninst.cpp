#include "PrepUninst.h"


void CPrepareUninst::Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect PosButTex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font)
{
	Log = TLog;
	Renderer = Render;

	Window.h = SCrH / 2;
	Window.w = SCrW / 2 + 100;
	Window.x = (SCrW / 2) - Window.w/2;
	Window.y = (SCrH / 2) - Window.h/2;

	SDL_Rect Position;
	int TxtHeight = 20;
	Position.x = Window.x + (Window.w / 4) - 100;
	Position.y = Window.y + (Window.h / 2) - TxtHeight - 10;
	Position.h = TxtHeight;
	Position.w = Window.w / 2;
	SDL_Color Col = { 0,0,0 };
	TxtColor = Col;

	SDL_Point PPos = {Position.x, Position.y};
	Descrition.Init(PPos, Font, 15,TLog, Render);
	Descrition.LoadFromRenderedTextUnicode(L"Niestandardowy plik odinstalowuj¹cy, proszê podaæ parametry do odinstalowania dla:", TxtColor);

	Position.y = Window.y + (Window.h / 2);
	PPos.y = Position.y;
	PrgName.Init(PPos, Font, 15,TLog, Render);
	PrgName.LoadFromRenderedText("puste", TxtColor);

	Position.x += 100;
	Position.y = Window.y + (Window.h / 2) + TxtHeight + 10;
	Parameters.Init(TLog, Position, Font, Render, Col, 15);
	Parameters.SetTxt("");

	Position.y = Position.y + TxtHeight + 10;
	Next.Init((Position.x + (Position.w / 2)) - PosButTex.w / 2, Position.y, PosButTex.w, PosButTex.h, TTexture, PosButTex.x, PosButTex.y,
		TLog, Render,"","", Font);
	Next.ChangeVis(true);
	Next.SetCaption("Dalej");
	BOK = true;
	Element = 0;
}

void CPrepareUninst::Render()
{
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // white
	SDL_RenderFillRect(Renderer, &Window); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Window); //border

	Descrition.Render();
	PrgName.Render();
	Parameters.Render();

	Next.Render();

}

void CPrepareUninst::HandleEvent(SDL_Event *e)
{
	
	if(!BOK)
	{
		Parameters.Input(e);

		//only if button clicked returns true
		if(Next.HandleEvent(e))
		{
			std::string Param = "";
			Param = Parameters.GetText();
			if(Param == "")
			{
				
				++Element;
				if( Element <  ToDo.size())
				{
					PrgName.LoadFromRenderedText(ToDo[Element].Name, TxtColor);
					
				}
				else BOK = true;
			}
			else
			{
				ToDo[Element].Uninsstr = ToDo[Element].Uninsstr + " " + Param;
				ToDo[Element].StrState = UStr_OK;
				++Element;
				if( Element  < ToDo.size() )
				{
					PrgName.LoadFromRenderedText(ToDo[Element].Name, TxtColor);
					
				}
				else BOK = true;
			}
		}
	}
}

void CPrepareUninst::CheckPrg(std::vector<CUinstPrgCont> Cont)
{
	bool BStrOK = true;
	for( int i = 0; i < Cont.size(); ++i)
	{
		if(Cont[i].StrState == UStr_EXE)
		{
			BStrOK = false;
			ToDo.push_back(Cont[i]);			
		}
		else if(Cont[i].StrState == UStr_Unknown) 
		{
			BStrOK = false;
			ToDo.push_back(Cont[i]);
		}
		else if(Cont[i].StrState == UStr_OK)
		{
			ClearStr.push_back(Cont[i]);
			
		}
	}
	if(!BStrOK)
	{
		PrgName.LoadFromRenderedText(Cont[0].Name, TxtColor);
		Element = 0;
	}
	BOK = BStrOK;
}

std::vector<CUinstPrgCont> CPrepareUninst::GetPrg()
{
	
	std::vector<CUinstPrgCont> Prglst = ClearStr;
	if(!ToDo.empty())
	{
		for(int i = 0; i < ToDo.size(); ++i)
		{
			if(ToDo[i].StrState == UStr_OK)	Prglst.push_back(ToDo[i]);
		}
		ToDo.erase(ToDo.begin(),ToDo.end());
	}

	ClearStr.erase(ToDo.begin(),ToDo.end());
	Element = 0;
	return Prglst;
}

bool CPrepareUninst::AllOK()
{
	return BOK;
}