#include "PrepUninst.h"


void CPrepareUninst::Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect PosButTex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font)
{
	Log = TLog;
	Renderer = Render;

	//creates window
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

	//////////////////////////
	//Sets button,input boxex and texts
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
	///////////////////////////
	BOK = true; //is all ok (when its not run first time its must be OK)
	Element = 0; // starting element
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
		Parameters.Input(e); // handle input 

		//only if button clicked returns true
		if(Next.HandleEvent(e))
		{
			std::string Param = "";
			Param = Parameters.GetText(); // get parameter from user
			if(Param == "")
			{
				// if not exist skip program
				++Element;
				if( Element <  ToDo.size())
				{
					PrgName.LoadFromRenderedText(ToDo[Element].Name, TxtColor);
					
				}
				else BOK = true;
			}
			else
			{
				// add parameters to uninstall string and go to next element
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
	//check is programs uninstall string OK
	for( int i = 0; i < Cont.size(); ++i)
	{
		if(Cont[i].StrState == UStr_EXE)
		{
			//if not OK add to ToDO list
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
			//if OK add to Ready list
			ClearStr.push_back(Cont[i]);
			
		}
	}
	if(!BStrOK)
	{
		//if something wrong wait for parameters
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
			//add OK element to ready list
			if(ToDo[i].StrState == UStr_OK)	Prglst.push_back(ToDo[i]);
		}
		ToDo.erase(ToDo.begin(),ToDo.end());
	}

	//return programs list with good strings
	ClearStr.erase(ToDo.begin(),ToDo.end());
	Element = 0;
	return Prglst;
}

bool CPrepareUninst::AllOK()
{
	return BOK;
}