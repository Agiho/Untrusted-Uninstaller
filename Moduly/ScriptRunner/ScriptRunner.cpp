#include "ScriptRunner.h"

void CScriptRunner::Init(CLog *TLog, SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH
		, std::string MainLoc, std::string FontPath)
{
	BActive = false;
	BStarted = false;

	Log = TLog;

	Renderer = Render;

	User = "";

	Pass = "";

	Window = Size;

	SDL_Rect ContPos = Size;

	SDL_Color Col = {0,0,0};

	SDL_Point PPosDesc = {ContPos.x +1, ContPos.y + 1};
	Descr.Init(PPosDesc,FontPath, 16, TLog, Render);
	Descr.LoadFromRenderedTextUnicode(L"Wybierz skrypty ,które zostana uruchomione",Col);

	PPosDesc.y = PPosDesc.y + 17;
	Descr2.Init(PPosDesc,FontPath, 16, TLog, Render);
	Descr2.LoadFromRenderedTextUnicode(L"po procesie odinstalowywania",Col);

	ContPos.x = ContPos.x + 10; 
	ContPos.w = ContPos.w - But2W - 20;
	ContPos.y = ContPos.y + PPosDesc.y/2 + 10;
	ContPos.h = ContPos.h - ButH*2 - PPosDesc.y;


	//std::vector<SScriptInfo> ScriptsNames;
	MainLoc = MainLoc + "Scripts\\";
	//get scripts info
	///
	CFilesList List;
	List.SetLog(TLog);
	List.Read("Scripts//*"); // set folder with scripts
	auto NamesList = List.GetFileNames(); //get filenames
	
	for (int i = 0; i < NamesList.size(); ++i)
	{

		//get info about every file name in directory and add to full path main directory
		SScriptInfo Script;
		Script.Name = NamesList[i];
		Script.FullPath = MainLoc + NamesList[i];
		Script.BChecked = false;
		ScriptNfo.push_back(Script);
	}
	///

	ChkBoxCont.Init(TLog,ContPos,But2W,0,0,Render,&ScriptNfo,FontPath,Slider);

	ContPos.y = ContPos.y + ContPos.h + 1;
	ContPos.h = ButH;

	OK.Init(ContPos.x + (Window.w/2) - ButW/2, ContPos.y + ButH, ButW,ButH , Buttons,0,0,TLog, Render, "", "", FontPath);
	OK.SetDiam(ButW, ButH - 10);
	OK.SetCaption("OK");
}

void CScriptRunner::Activate()
{
	BActive = true;
}

bool CScriptRunner::IsActive()
{
	return BActive;
}

void CScriptRunner::AddCred(std::string TUser, std::string SPass)
{
	User = TUser;
	Pass = SPass;
}

void CScriptRunner::RunScript(std::vector<std::string> Where)
{
	BStarted = true;
	//erasing old list and crreating list of selected scripts
	if (!ScriptLaunch.empty()) ScriptLaunch.erase(ScriptLaunch.begin(), ScriptLaunch.end());
	ScriptLaunch = ChkBoxCont.GetChk();
	
	if (ScriptLaunch.size()) //if there is something to do
	{
		for (int i = 0; i < Where.size(); ++i)
		{
			CopyFile( ("Scripts\\" + ScriptLaunch[0].Name).c_str(), ("\\\\" + Where[i] + "\\c$\\temp\\" + ScriptLaunch[0].Name).c_str() , FALSE ); //copying file using WinAPI
			
			CWMIRun *WMI = new CWMIRun;
			WMI->InsertLog(Log);
			WMI->SecPrevAdded(true); //there shoudl always exist WMI object which connect somewhere before using this class
			WMI->ConnectWMI(Where[i], User, Pass, true); //connect

			int Error = WMI->ExecMethod("\\c$\\temp\\" + ScriptLaunch[0].Name); //execute first script
			if (Error)
			{
				//show messagebox
				CMsgBox InfoMsg;
				InfoMsg.IstertLog(Log);
				InfoMsg.MakeOK();
				InfoMsg.ShowMsg("Problem z wykonaniem instrukcji ", "Niepowodzenie uruchomienia skryptu na komputerze: " + WMI->Getloc());
				Log->WriteTxt("Can't run scripts on: " + WMI->Getloc());
			}
			else
			{
				for (int j = 1; j < ScriptLaunch.size(); ++j) //rest of scripts
				{
					CopyFile( ("Scripts\\" + ScriptLaunch[j].Name).c_str(), ("\\\\" + Where[i] + "\\c$\\temp\\" + ScriptLaunch[j].Name).c_str() , FALSE );
					WMI->ExecMethod(ScriptLaunch[j].FullPath);
				}
				Log->WriteTxt("All scripts launched successfully on: " + WMI->Getloc());
			}
			ScriptLaunch.erase(ScriptLaunch.begin(), ScriptLaunch.end());
			ScriptLaunch.clear();

			//show messagebox
			CMsgBox InfoMsg;
			InfoMsg.IstertLog(Log);
			InfoMsg.MakeOK();
			InfoMsg.ShowMsg("Uruchomiono wszystkie skrypty", "Uruchomiono wszystkie wybrane skrypty");	
			delete WMI;
		}
	}
	BActive = false;
}

bool CScriptRunner::HandleEvent(SDL_Event *e)
{
	ChkBoxCont.HandleEvent(e);

	if (OK.HandleEvent(e))
	{
		BActive = false;
		return true;
	}
	return false;
}

void CScriptRunner::Render()
{
	//Window
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // color
	SDL_RenderFillRect(Renderer, &Window); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Window); //border

	Descr.Render();
	Descr2.Render();

	ChkBoxCont.Render();

	OK.Render();
}

bool CScriptRunner::IsStarted()
{
	return BStarted;
}

void CScriptRunner::SetNotStarted()
{
	BStarted = false;
}