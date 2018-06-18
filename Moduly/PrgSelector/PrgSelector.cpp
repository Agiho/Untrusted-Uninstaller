#include "PrgSelector.h"

void CPrgSelector::Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton)
{
	BRenderPrg = false;
	int ButH = 50;
	int ButW = 100;
	Log = TLog;

	WMI = TWMI;

	SDL_Color C = {0,0,0};
	TxtColor = C;

	Plus.Init(ScrW - ButW, ButH , ButW/2, ButH, StdButton, ButW, 0, TLog, Render, "", "",FontPath);
	FromFile.Init(ScrW - ButW, ButH*2, ButW, ButH, StdButton, 0,0, TLog, Render, "", "",FontPath);
	FromFile.SetCaption("Z Pliku");
	Begin.Init(ScrW - ButW - 10, ScrH - ButH - 10, ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Begin.SetCaption("Start");
	
	SDL_Point Pos;
	Pos.x = 10;
	Pos.y = ScrH - ButH - 10;
	HowManyUninst.Init(Pos,FontPath, ButH /2 ,TLog, Render);
	HowManyUninst.LoadFromRenderedText("Zaznaczono do odinstalwania: 0", TxtColor);
	Pos.x = 10;
	Pos.y = ButH + 10;
	WhereConnected.Init(Pos,FontPath, ButH /2,TLog, Render);
	WhereConnected.LoadFromRenderedText("Pod³¹czony do: ", TxtColor);
	Pos.x = ScrW - ButW*3;
	Pos.y = ButH*2 + ButH/2;
	WhereInstall.Init(Pos,FontPath, ButH / 2,TLog, Render);
	WhereInstall.LoadFromRenderedTextUnicode(L"Wykonaj te¿ na:", TxtColor);
	SDL_Rect RectPos;
	RectPos.x = ScrW - ButW*3;
	RectPos.y = ButH;
	RectPos.w = ButW*2;
	RectPos.h = ButH;
	IPBox.Init(TLog, RectPos, FontPath, Render, TxtColor, ButH/2);
	IPBox.SetTxt("");

	SDL_Rect Frame;
	Frame.w = (60 + ScrW/2);
	Frame.h = (ScrH/2) + 100;
	Frame.x =  50;
	Frame.y = ScrH - Frame.h - ButH*2;

	PrgChkBox.Init(TLog,Frame, 50, ScrW ,ScrH ,Render, Programslst, FontPath, FirstSlid);

	Frame.w = (ButW*2);
	Frame.h = (ScrH/2) + 100;
	Frame.x = ScrW - (ButW*2) - 100;
	Frame.y = ScrH - Frame.h - ButH*2;

	CompChkBox.Init(TLog,Frame,50, ScrW, ScrH, Render, &CompNames, FontPath, FirstSlid);
	NrCheckedPrg = 0;
}

void CPrgSelector::SetWhereConnected(std::string Name)
{
	std::wstring temp(Name.length(),L' ');
	std::copy(Name.begin(), Name.end(), temp.begin());
	WhereConnected.LoadFromRenderedTextUnicode(L"Pod³¹czony do: " + temp, TxtColor);
	
}

void CPrgSelector::Update()
{
	if(NrCheckedPrg != PrgChkBox.Checked())
	{
		NrCheckedPrg = PrgChkBox.Checked();
		std::stringstream Mystream;
		Mystream << "Zaznaczono do odinstalwania: " << NrCheckedPrg;
		HowManyUninst.LoadFromRenderedText(Mystream.str(), TxtColor);
	}
}

void CPrgSelector::HandleEvent(SDL_Event *e)
{
	if(Plus.HandleEvent(e))
	{
		if(IPBox.GetText() != "")
		{
			SCompInfo TComp;
			TComp.Name = IPBox.GetText();
			TComp.BChecked = true;
			CompChkBox.AddNewOne(TComp);
			IPBox.SetTxt("");
		}
	}
	if(FromFile.HandleEvent(e))
	{
		CBasicFileDialog Dial;
		Dial.CreateOpenFileDialog(NULL, "Wybierz Plik", "C:\\", "All files(*.*)\0*.*\0TextFiles(*.txt)\0*.txt\0", 2);
		char* path = Dial.ReturnLastPath();
		Log->WriteTxt(path);
	}
	if(Begin.HandleEvent(e))
	{
		BeginUninstall();
	}

	IPBox.Input(e);

	PrgChkBox.HandleEvent(e);
	CompChkBox.HandleEvent(e);
}

void CPrgSelector::Render()
{
	// textboxes and inputbox
	HowManyUninst.Render();
	WhereConnected.Render();
	WhereInstall.Render();
	IPBox.Render();

	//buttons
	Plus.Render();
	FromFile.Render();
	Begin.Render();

	//checkboxes
	if(BRenderPrg)PrgChkBox.Render();
	CompChkBox.Render();
}

void CPrgSelector::SetPrg(std::vector<CUinstPrgCont> *Prg)
{
	BRenderPrg = true;
	PrgChkBox.SetNewList(Prg);
}

void CPrgSelector::BeginUninstall()
{
	std::vector<CUinstPrgCont> Uninstall = PrgChkBox.GetChk();
	if(!(Uninstall.empty()))
	{
		for(int i = 0 ; i < Uninstall.size(); ++i)
		{
			WMI->ExecMethod(Uninstall[i].Uninsstr);
		}
	}

	if(!(CompNames.empty()))
	{
		CWMIRun *Others = new CWMIRun[CompNames.size()];
		for(int i = 0 ; i < CompNames.size(); ++i)
		{

			if(!(Uninstall.empty()))
			{
				for(int i = 0 ; i < Uninstall.size(); ++i)
				{
					Others[i].InsertLog(Log);
					Others[i].SecPrevAdded(true);
					Others[i].ConnectWMI(CompNames[i].Name);
					Others[i].ExecMethod(Uninstall[i].Uninsstr);
				}
			}

		}
		delete [] Others;
	}
}