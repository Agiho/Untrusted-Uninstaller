#include "PrgSelector.h"


CPrgSelector::CPrgSelector()
{
	BNeedPrepare = false;
	BRenderPrg = false;
	BShowTerminator = false;
	BShowScriptRunner = false;
	BFilter = false;

	WMI = nullptr;
	Log = nullptr;
	UninstMgr = nullptr;
}

void CPrgSelector::Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton)
{
	BNeedPrepare = false;
	BRenderPrg = false;
	BFilter = false;
	BShowTerminator = false;
	BShowScriptRunner = false;

	int ButH = 50;
	int ButW = 100;
	Log = TLog;

	WMI = TWMI;

	SDL_Color C = {0,0,0};
	TxtColor = C;

	//Buttons initialization
	Plus.Init(ScrW - ButW, ButH , ButW/2, ButH, StdButton, ButW, 0, TLog, Render, "", "",FontPath);
	Plus.SetDiam(ButW/2 - 10, ButH - 10);
	FromFile.Init(ScrW - ButW, ButH*2, ButW, ButH, StdButton, 0,0, TLog, Render, "", "",FontPath);
	FromFile.SetDiam(ButW, ButH -10);
	FromFile.SetCaption("Z Pliku");
	Begin.Init(ScrW - ButW - 10, ScrH - ButH - 10, ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Begin.SetDiam(ButW, ButH -10);
	Begin.SetCaption("Start");
	SelectScript.Init(ScrW - ButW - 10, ScrH - 2*ButH - 20, ButW, ButH, StdButton, 0, 0, TLog, Render, "", "", FontPath);
	SelectScript.SetDiam(ButW, ButH - 10);
	SelectScript.SetCaption("Skrypty");
	Terminate.Init(ScrW - ButW*3 - 5, ScrH - ButH - 10, ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Terminate.SetDiam(ButW*2 - 10, ButH - 10);
	Terminate.SetCaption("Przerwij proces");
	Filter.Init(50 + (60 + ScrW/2) - ButW/2, ScrH - ButH - 10 ,  ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Filter.SetDiam(ButW, ButH - 10);
	Filter.SetCaption("Filtruj");

	//text initialization
	SDL_Point Pos;
	Pos.x = 10;
	Pos.y = ScrH - ButH - 10;
	HowManyUninst.Init(Pos,FontPath, ButH/2 - 5 ,TLog, Render);
	HowManyUninst.LoadFromRenderedText("Wybrano do odinstalowania: 0", TxtColor);
	Pos.x = 10;
	Pos.y = ButH + 10;
	WhereConnected.Init(Pos,FontPath, ButH/2 - 5,TLog, Render);
	WhereConnected.LoadFromRenderedText("Pod³¹czony do: ", TxtColor);
	Pos.x = ScrW- ButW*6;
	Pos.y = ButH + 10;
	IPInfo.Init(Pos,FontPath, (ButH/2) - 5,TLog, Render);
	IPInfo.LoadFromRenderedText("Adres IP dodatkowego komputera:", TxtColor);
	Pos.x = ScrW - ButW*3;
	Pos.y = ButH*2 + ButH/2;
	WhereInstall.Init(Pos,FontPath, ButH/2 - 5,TLog, Render);
	WhereInstall.LoadFromRenderedTextUnicode(L"Wykonaj te¿ na:", TxtColor);
	SDL_Rect RectPos;
	RectPos.x = ScrW - ButW*3;
	RectPos.y = ButH;
	RectPos.w = ButW*2;
	RectPos.h = ButH - 10;
	IPBox.Init(TLog, RectPos, FontPath, Render, TxtColor, ButH/2 - 2);
	IPBox.SetTxt("");
	RectPos.x = (60 + ScrW/2) - RectPos.w;
	RectPos.y = ScrH - ButH - 10;
	InputFilter.Init(TLog, RectPos, FontPath, Render, TxtColor, (ButH/2) - 2);
	InputFilter.SetTxt("");

	//checkboxes initialization with empty list
	SDL_Rect Frame;
	Frame.w = (60 + ScrW/2);
	Frame.h = (ScrH/2) + 140;
	Frame.x =  50;
	Frame.y = ScrH - Frame.h - ButH - 15;

	PrgChkBox.Init(TLog,Frame, 50, ScrW ,ScrH ,Render, Programslst, FontPath, FirstSlid);

	Frame.w = (ButW*2);
	Frame.h = (ScrH/2) + 140 - ButH - 20;
	Frame.x = ScrW - (ButW*2) - 100;
	Frame.y = ScrH - Frame.h - 2*ButH - 15 - 20;

	CompChkBox.Init(TLog,Frame,50, ScrW, ScrH, Render, &CompNames, FontPath, FirstSlid);
	NrCheckedPrg = 0;


	//program checker  window
	SDL_Rect butpos;
	butpos.x = 0;
	butpos.y = 0;
	butpos.w = 100;
	butpos.h = 50;
	WPrepUninst.Init(TLog, StdButton, Render, butpos, ScrW, ScrH, FontPath);

	
	
}

void CPrgSelector::SetWhereConnected(std::string Name)
{
	//adds to text where current connected
	ConnectedTo = Name;
	std::wstring temp(Name.length(),L' ');
	std::copy(Name.begin(), Name.end(), temp.begin());
	WhereConnected.LoadFromRenderedTextUnicode(L"Pod³¹czony do: " + temp, TxtColor);
}

void CPrgSelector::SetUninstMgr(CUninstMgr *Mgr)
{
	UninstMgr = Mgr;
}

void CPrgSelector::SetTerminator(CTerminator *TTerminator)
{
	Terminator = TTerminator;
}

void CPrgSelector::SetScriptRunner(CScriptRunner *TScriptRunner)
{
	ScriptRunner = TScriptRunner;
}

void CPrgSelector::Update()
{
	//update checboxes and info about how many checked
	if(NrCheckedPrg != PrgChkBox.Checked())
	{
		NrCheckedPrg = PrgChkBox.Checked();
		std::stringstream Mystream;
		Mystream << "Wybrano do odinstalowania: " << NrCheckedPrg;
		HowManyUninst.LoadFromRenderedText(Mystream.str(), TxtColor);
	}
	// update checkprogram window when need prepare
	if(BNeedPrepare)
	{
		if(WPrepUninst.AllOK())BeginUninstall(WPrepUninst.GetPrg());		
		BNeedPrepare = !(WPrepUninst.AllOK());		
	}

	if(UninstMgr != nullptr)
	{
		UninstMgr->Update();
		if(UninstMgr->AllEnd()) 
		{

			if(!(ScriptRunner->IsStarted())) //if not already started
			{
				// Show MessageBox with info
				CMsgBox InfoMsg;
				InfoMsg.IstertLog(Log);
				InfoMsg.MakeOK();
				InfoMsg.ShowMsg("Procesy odinstalowywania" , "Wszystkie procesy odinstalowywania wykonane");

				std::vector<std::string> Comps;
	
				Comps.push_back(WMI->Getloc());

				if(!CompNames.empty())
				{
					for(int i = 0; i < CompNames.size(); ++i)
					{
						Comps.push_back(CompNames[i].Name); //adds computer adressess from computers list to vector
					}
				}
				
				ScriptRunner->RunScript(Comps); // run selected scripts on computers

			}
		}
	}
	
}

void CPrgSelector::HandleEvent(SDL_Event *e)
{
	if (!BNeedPrepare && !BShowTerminator && !BShowScriptRunner) // handle this when window for preparing string is bot active
	{
		if (Plus.HandleEvent(e) || (IPBox.Input(e) == SDLK_RETURN)) //plus button events and input box
		{
			if (IPBox.GetText() != "")
			{
				SCompInfo TComp;
				TComp.Name = IPBox.GetText(); //get IP/name of computer from input box
				TComp.BChecked = true;
				CompChkBox.AddNewOne(TComp); //add to checkbox container
				IPBox.SetTxt("");
			}
		}
		if (FromFile.HandleEvent(e)) //from file button clicked
		{
			CBasicFileDialog Dial;
			Dial.CreateOpenFileDialog(NULL, "Wybierz Plik", "C:\\", "All files(*.*)\0*.*\0TextFiles(*.txt)\0*.txt\0", 2); //open file dialog
			const char* path = Dial.ReturnLastPath(); //get path to file
			Log->WriteTxt("Reading computers list from file " + std::string(path));
			FileRead(path); //load computers list from file
		}
		if (Begin.HandleEvent(e)) //begin button clicked
		{
			CMsgBox MsgYesNo;
			MsgYesNo.IstertLog(Log);
			MsgYesNo.MakeYesNo();
			if (MsgYesNo.ShowMsg("Odinstalowywanie Oprogramowania", "Czy na pewno chcesz by te programy odinstalowano?") == 1)
			{
				WPrepUninst.CheckPrg(PrgChkBox.GetChk()); //check that programs sings are correct
				if (WPrepUninst.AllOK()) BeginUninstall(WPrepUninst.GetPrg()); //if ok begin uninsall			
				else BNeedPrepare = true; //if not need prepare it
			}
		}
		if (SelectScript.HandleEvent(e))// ScriptRunner button clicked
		{
			BShowScriptRunner = true;
		}
		if (Terminate.HandleEvent(e)) //terminator button clicked
		{
			BShowTerminator = true;
		}
		if (Filter.HandleEvent(e) || (InputFilter.Input(e) == SDLK_RETURN)) //filter button events and input box events and waiting for enter button
		{
			auto FilterTxt = InputFilter.GetText();
			if ((FilterTxt == "") || (FilterTxt == " ")) // if there is no filter
			{
				if (BFilter)
				{
					BFilter = false;
					PrgChkBox.SetNewList(Uninstlst);
					if (!Filtered.empty())
					{
						for (int i = 0; i < Filtered.size(); ++i)
						{
							(*FilterMainCon[i]) = Filtered[i];
						}
						Filtered.erase(Filtered.begin(), Filtered.end());
						FilterMainCon.erase(FilterMainCon.begin(), FilterMainCon.end());
					}
				}
			}
			else
			{
				if (!Uninstlst->empty())
				{
					if (!Filtered.empty())
					{
						for (int i = 0; i < Filtered.size(); ++i)
						{
							(*FilterMainCon[i]) = Filtered[i];
						}
						Filtered.erase(Filtered.begin(), Filtered.end());
						FilterMainCon.erase(FilterMainCon.begin(), FilterMainCon.end());
					}
					for (int i = 0; i < Uninstlst->size(); ++i)
					{
						if ((*Uninstlst)[i].Name.find(FilterTxt.c_str()) != std::string::npos)
						{

							Filtered.push_back((*Uninstlst)[i]);
							FilterMainCon.push_back(&((*Uninstlst)[i]));
							PrgChkBox.SetNewList(&Filtered);
							BFilter = true;
						}
					}
				}
			}
		}

		//checkboxes events
		PrgChkBox.HandleEvent(e);
		CompChkBox.HandleEvent(e);
	}
	else if (BNeedPrepare)
	{
		WPrepUninst.HandleEvent(e); //prepare window events
	}
	else if (BShowTerminator)
	{
		if (Terminator->HandleEvent(e)) BShowTerminator = false;
	}
	else if (BShowScriptRunner)
	{
		if (ScriptRunner->HandleEvent(e)) BShowScriptRunner = false;
	}
}

void CPrgSelector::Render()
{
	// textboxes and inputbox
	HowManyUninst.Render();
	WhereConnected.Render();
	WhereInstall.Render();
	IPInfo.Render();
	IPBox.Render();
	InputFilter.Render();

	//buttons
	Plus.Render();
	FromFile.Render();
	Begin.Render();
	SelectScript.Render();
	Filter.Render();
	Terminate.Render();

	//checkboxes
	if(BRenderPrg)PrgChkBox.Render();
	CompChkBox.Render();
	if(BNeedPrepare)
	{
		WPrepUninst.Render();
	}
	if(BShowTerminator)
	{
		Terminator->Render();
	}
	if (BShowScriptRunner)
	{
		ScriptRunner->Render();
	}
}

void CPrgSelector::SetPrg(std::vector<CUinstPrgCont> *Prg)
{
	//adds new program list
	BRenderPrg = true;
	Uninstlst = Prg;
	
	std::sort (Prg->begin() , Prg->end());
	PrgChkBox.SetNewList(Prg);
}


void CPrgSelector::FileRead(std::string Path)
{
	File.Init(Path.c_str(), std::ios_base::in);
	
	if(File.AllOk())
	{		
		//stream variable
		std::stringstream stream;
		stream.clear();
		//set reading from begin of file
		File.SetReadPos();
		// text from file
		char Text[65]; 

		//temporary file
		SCompInfo TComp;
		TComp.BChecked = true;
			
		while(!File.EoF())
		{
			//read IP from file
			File.GetLineTxt(Text, 64);

			if((std::string(Text) != "") && (std::string(Text) != " "))
			{
				TComp.Name = Text;
				CompChkBox.AddNewOne(TComp);
			}
		}
		
	}
}

void CPrgSelector::BeginUninstall(std::vector<CUinstPrgCont> Uninstall)
{

	std::vector<std::string> Comps;
	
	Comps.push_back(WMI->Getloc());

	if(!CompNames.empty())
	{
		for(int i = 0; i < CompNames.size(); ++i)
		{
			Comps.push_back(CompNames[i].Name);
		}
	}

	if(!Filtered.empty())
	{
		for(int i = 0; i < Filtered.size(); ++i)
		{
			(*FilterMainCon[i]) = Filtered[i];
		}
		Filtered.erase(Filtered.begin(), Filtered.end());
		FilterMainCon.erase(FilterMainCon.begin(), FilterMainCon.end());
	}

	if(!(Uninstall.empty())) //if there is programs to uninstall
	{
		UninstMgr->StartUninstall(Comps,Uninstall);
		std::vector<CUinstPrgCont> TempCont;
		//remove checked program from the list
		for(int i = 0; i < (*Uninstlst).size(); ++i)
		{
			if(!((*Uninstlst)[i].BChecked)) TempCont.push_back((*Uninstlst)[i]);
		}
		(*Uninstlst).erase((*Uninstlst).begin(), (*Uninstlst).end());
		(*Uninstlst) = TempCont;
		PrgChkBox.SetNewList(Uninstlst);
		//reset counter
		PrgChkBox.ResetChecked();		
	}	
}