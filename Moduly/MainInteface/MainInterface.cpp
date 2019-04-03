#include "MainInterface.h"

void CMainInterface::Init(CLog *TLog, CConfig *Cfg, ChkPrg *TChecker , CWMIRun *WMI , SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string FontPath)
{
	Phase = LOCALCH; // set starting phase
	Log = TLog;
	ScrWidth = ScrW;
	ScrHeight = ScrH;
	TexCont.Init(Render, TLog);
	LoadPos(TLog, Render,1,FontPath); // set butons position

	Checker = TChecker;
	RExec = WMI;

	SDL_Rect butpos;
	butpos.x = 0;
	butpos.y = 0;
	butpos.w = 100;
	butpos.h = 50;
	WAIWin.Init(TLog, TexCont.LoadTex(GetTexbyID(1)), Render, butpos, ScrW, ScrH,  FontPath);
	Select.Init(TLog, RExec, ScrW, ScrH, Render, &Programs, FontPath, TexCont.LoadTex(GetTexbyID(2)), TexCont.LoadTex(GetTexbyID(3)), TexCont.LoadTex(GetTexbyID(1)));

	UninstMgr.Init(TLog,&Terminator);
	Select.SetUninstMgr(&UninstMgr);

	//process terminator
	SDL_Rect TerminSize;
	TerminSize.h = ScrH - 2*butpos.h;
	TerminSize.y = butpos.h;
	TerminSize.w = 300;
	TerminSize.x = ScrW/2 - TerminSize.w/2;
	Terminator.Init(TLog, Render, TerminSize, TexCont.LoadTex(GetTexbyID(2)), TexCont.LoadTex(GetTexbyID(1)), butpos.w, butpos.w/2, butpos.h, FontPath);
	Select.SetTerminator(&Terminator);

	//script runner
	SDL_Rect ScriptSize;
	ScriptSize.h = ScrH - 2 * butpos.h;
	ScriptSize.y = butpos.h;
	ScriptSize.w = 300;
	ScriptSize.x = ScrW / 2 - ScriptSize.w / 2;
	ScriptRunner.Init(TLog, Render, ScriptSize, TexCont.LoadTex(GetTexbyID(2)), TexCont.LoadTex(GetTexbyID(1)), butpos.w, butpos.w / 2, butpos.h, Cfg->GetMainLoc(), FontPath);
	Select.SetScriptRunner(&ScriptRunner);

	//infobox about getting program list;
	SDL_Rect InfoSize;
	InfoSize.x = 100;
	InfoSize.w = ScrW - 200;
	InfoSize.h = ScrH / 2;
	InfoSize.y = (ScrH / 2) - InfoSize.h/2;
	SDL_Color Col = {0,0,0};
	Info.Init(TLog,InfoSize,Render,FontPath,Col);
	Info.SetInfo(L"Proszê czekaæ, trwa pobieranie listy programów...");

	BRenderInfo = false;
	BQuit = false;

}

void CMainInterface::Render()
{
	switch(Phase)
	{
	case LOCALCH:
		Local.Render();
		Remote.Render();
		if(BRenderInfo) Info.Render();

		break;

	case GETIP:

		WAIWin.Render();
		if(BRenderInfo) Info.Render();

		break;

	case PRG_SELECT:

		Select.Render();

		break;

	case UNINST_STATUS:

		break;
	}
} 

void CMainInterface::Update()
{
	Select.Update();
}

void CMainInterface::HandleEvent(SDL_Event *e)
{
	switch(Phase)
	{
	case LOCALCH:
		if(!BRenderInfo)
		{
			if (Local.HandleEvent(e))
			{
				BRenderInfo = true;
			}
			
		}
		else 
		{
			//Login to local Computer
			Programs = Checker->GetPrgandPath();
			RExec->ConnectWMI();
			Select.SetPrg(&Programs);
			Select.SetWhereConnected("Ten Komputer");
			UninstMgr.AddCred();
			ScriptRunner.AddCred();
			Phase = PRG_SELECT;
			BRenderInfo = false;
		}
		
		//change to window where user input info about login
		if(Remote.HandleEvent(e)) Phase = GETIP;

		break;

	case GETIP:

		if(BRenderInfo)
		{
			//getting info
			IP = WAIWin.GetIP();
			USER = WAIWin.GetUser();
			PASSWORD = WAIWin.GetPassword();
	
			//startring service
			CRSrvStart RSrv;
			RSrv.InsertLog(Log);
			RSrv.StartRemoteService(IP,"RemoteRegistry");
			
			

			//getting program list
			Checker->InstertWMIPointer(RExec);
			Programs = Checker->GetPrgandPath(IP, USER, PASSWORD);

			if(USER == "Domniemany")
			{
				RExec->ConnectWMI(IP);
				UninstMgr.AddCred();
				ScriptRunner.AddCred();
			}
			else
			{
				RExec->ConnectWMI(IP, USER, PASSWORD);
				UninstMgr.AddCred(USER, PASSWORD);
				ScriptRunner.AddCred(USER, PASSWORD);
			}
			

			Select.SetPrg(&Programs);
			Select.SetWhereConnected(IP);

			// stoping service
			RSrv.StopRemoteService(IP,"RemoteRegistry");

			Phase = PRG_SELECT;

			BRenderInfo = false;

		}
		else if (WAIWin.HandleEvent(e))
		{
			
			BRenderInfo = true;

		}
		break;

	case PRG_SELECT:

		Select.HandleEvent(e);

		break;

	case UNINST_STATUS:

		break;
	}
}

bool CMainInterface::IsQuit()
{
	return BQuit;
}

void CMainInterface::LoadPos(CLog *TLog, SDL_Renderer* Render, int ID, std::string Font)
{
	unsigned int FirstW = 100; //first 2 buttons width
	unsigned int FirstH = 50; //first 2 buttons height
	Local.Init(((ScrWidth/2) - FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render,"","",Font);
	Local.SetCaption("Lokalny");
	Remote.Init(((ScrWidth/2) + FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render,"","",Font);
	Remote.SetCaption("W sieci");

}

const char* CMainInterface::GetTexbyID(int ID)
{
	switch (ID)
	{
	case 1:
		return "Textures/Buttons.png";
	case 2:
		return "Textures/Slider1.png";
	case 3:
		return "Textures/Slider2.png";
	}
}