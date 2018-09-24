#include "Terminator.h"


void CTerminator::Init(CLog *TLog, SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH
		, std::string FontPath)
{
	Log = TLog;

	Renderer = Render;

	Window = Size;

	SDL_Rect ContPos = Size;

	SDL_Color Col = {0,0,0};

	SDL_Point PPosDesc = {ContPos.x +1, ContPos.y + 1};
	Descr.Init(PPosDesc,FontPath, 16, TLog, Render);
	Descr.LoadFromRenderedTextUnicode(L"Wpisz dok³adn¹ nazwê procesu który ma",Col);
	
	PPosDesc.y = PPosDesc.y + 17;
	Descr2.Init(PPosDesc,FontPath, 16, TLog, Render);
	Descr2.LoadFromRenderedTextUnicode(L"zostaæ zakoñczony przed odinstalowaniem",Col);
	
	ContPos.x = ContPos.x + 10; 
	ContPos.w = ContPos.w - But2W - 20;
	ContPos.y = ContPos.y + PPosDesc.y/2 + 10;
	ContPos.h = ContPos.h - ButH*2 - PPosDesc.y;

	ChkBoxCont.Init(TLog,ContPos,But2W,0,0,Render,&Processes,FontPath,Slider);
	
	ContPos.y = ContPos.y + ContPos.h + 1;
	ContPos.h = ButH;


	InputBox.Init(TLog,ContPos, FontPath, Render, Col, (ButH/2) - 2);
	InputBox.ChangeActiv(true);

	Plus.Init(ContPos.x + ContPos.w, ContPos.y, But2W, ButH,Buttons,ButW, 0, TLog, Render, "", "",FontPath);
	OK.Init(ContPos.x + (Window.w/2) - ButW/2, ContPos.y + ButH, ButW,ButH , Buttons,0,0,TLog, Render, "", "", FontPath);
	OK.SetDiam(ButW, ButH - 10);
	OK.SetCaption("OK");

}

void CTerminator::AddProcesses(std::vector<std::string> ProcNames)
{
	if(!ProcNames.empty())
	{
		for(int i = 0; i < ProcNames.size(); ++i)
		{
			SProcessInfo Proc;
			Proc.Name = ProcNames[i];
			Proc.BChecked = true;
			Processes.push_back(Proc);
		}
	}
}

void CTerminator::AddOne(std::string ProcName)
{
	SProcessInfo Proc;
	Proc.Name = ProcName;
	Proc.BChecked = true;
	Processes.push_back(Proc);
}

void CTerminator::ClrLst()
{
	Processes.erase(Processes.begin(),Processes.end());
	ChkBoxCont.ResetChecked();
}

std::vector<std::string> CTerminator::GetProcesses()
{
	std::vector<std::string> Return;

	if(!Processes.empty())
	{
		for(int i = 0; i < Processes.size(); ++i)
		{
			if(Processes[i].BChecked)
			{
				Return.push_back(Processes[i].Name);
			}
		}
	}
	else
	{
		Return.push_back("Empty");
	}

	return Return;
}

void CTerminator::Activate()
{
	BActive = true;
}

bool CTerminator::IsActive()
{
	return BActive;
}

void CTerminator::Terminate(CWMIRun *WMI)
{
	if(!Processes.empty())
	{
		for(int i = 0; i < Processes.size(); ++i)
		{
			if(Processes[i].BChecked)
			{
				WMI->Terminate((Processes[i].Name));
			}
		}
	}
}

void CTerminator::Terminate(CWMIRun *WMI, std::vector<std::string> ProcNames)
{
	if(!ProcNames.empty())
	{
		for(int i = 0; i < ProcNames.size(); ++i)
		{
			WMI->Terminate(ProcNames[i]);
		}
	}
}

bool CTerminator::HandleEvent(SDL_Event *e)
{

	if(Plus.HandleEvent(e) || (InputBox.Input(e) == SDLK_RETURN))
	{
		if(InputBox.GetText() != "")
		{
			SProcessInfo TProc;
			TProc.Name = InputBox.GetText(); //get IP/name of computer from input box
			TProc.BChecked = true;
			ChkBoxCont.AddNewOne(TProc); //add to checkbox container
			InputBox.SetTxt("");
		}
		else return true;
	}

	if(OK.HandleEvent(e))
	{
		return true;
	}


	ChkBoxCont.HandleEvent(e);

	return false;
}

void CTerminator::Render()
{
	//Window
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // color
	SDL_RenderFillRect(Renderer, &Window); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Window); //border

	Plus.Render();
	OK.Render();

	InputBox.Render();

	ChkBoxCont.Render();
	Descr.Render();
	Descr2.Render();
}