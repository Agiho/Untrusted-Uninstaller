#include "PrgSelector.h"

void CPrgSelector::Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton)
{
	BNeedPrepare = false;
	BRenderPrg = false;
	int ButH = 50;
	int ButW = 100;
	Log = TLog;

	WMI = TWMI;

	SDL_Color C = {0,0,0};
	TxtColor = C;

	//Buttons initialization
	Plus.Init(ScrW - ButW, ButH , ButW/2, ButH, StdButton, ButW, 0, TLog, Render, "", "",FontPath);
	FromFile.Init(ScrW - ButW, ButH*2, ButW, ButH, StdButton, 0,0, TLog, Render, "", "",FontPath);
	FromFile.SetCaption("Z Pliku");
	Begin.Init(ScrW - ButW - 10, ScrH - ButH - 10, ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Begin.SetCaption("Start");
	

	//text initialization
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

	//checkboxes initialization with empty list
	SDL_Rect Frame;
	Frame.w = (60 + ScrW/2);
	Frame.h = (ScrH/2) + 140;
	Frame.x =  50;
	Frame.y = ScrH - Frame.h - ButH - 15;

	PrgChkBox.Init(TLog,Frame, 50, ScrW ,ScrH ,Render, Programslst, FontPath, FirstSlid);

	Frame.w = (ButW*2);
	Frame.h = (ScrH/2) + 140;
	Frame.x = ScrW - (ButW*2) - 100;
	Frame.y = ScrH - Frame.h - ButH - 15;

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

void CPrgSelector::Update()
{
	//update checboxes and info about how many checked
	if(NrCheckedPrg != PrgChkBox.Checked())
	{
		NrCheckedPrg = PrgChkBox.Checked();
		std::stringstream Mystream;
		Mystream << "Zaznaczono do odinstalwania: " << NrCheckedPrg;
		HowManyUninst.LoadFromRenderedText(Mystream.str(), TxtColor);
	}
	// update checkprogram window when need prepare
	if(BNeedPrepare)
	{
		if(WPrepUninst.AllOK())BeginUninstall(WPrepUninst.GetPrg());		
		BNeedPrepare = !(WPrepUninst.AllOK());		
	}
}

void CPrgSelector::HandleEvent(SDL_Event *e)
{
	if(!BNeedPrepare) // handle this when window for preparing string is bot active
	{
		if(Plus.HandleEvent(e)) //plus button event
		{
			if(IPBox.GetText() != "")
			{
				SCompInfo TComp;
				TComp.Name = IPBox.GetText(); //get IP/name of computer from input box
				TComp.BChecked = true;
				CompChkBox.AddNewOne(TComp); //add to checkbox container
				IPBox.SetTxt("");
			}
		}
		if(FromFile.HandleEvent(e)) //from file button clicked
		{
			CBasicFileDialog Dial;
			Dial.CreateOpenFileDialog(NULL, "Wybierz Plik", "C:\\", "All files(*.*)\0*.*\0TextFiles(*.txt)\0*.txt\0", 2); //open file dialog
			const char* path = Dial.ReturnLastPath(); //get path to file
			Log->WriteTxt("Reading computers list from file " + std::string(path));
			FileRead(path); //load computers list from file
		}
		if(Begin.HandleEvent(e)) //begin button clicked
		{
			WPrepUninst.CheckPrg(PrgChkBox.GetChk()); //check that programs sings are correct
			if(WPrepUninst.AllOK()) BeginUninstall(WPrepUninst.GetPrg()); //if ok begin uninsall			
			else BNeedPrepare = true; //if not need prepare it
		}

		IPBox.Input(e); //input to inputbox

		//checkboxes events
		PrgChkBox.HandleEvent(e);
		CompChkBox.HandleEvent(e);
	}
	else
	{
		WPrepUninst.HandleEvent(e); //prepare window events
	}
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
	if(BNeedPrepare)
	{
		WPrepUninst.Render();
	}
}

void CPrgSelector::SetPrg(std::vector<CUinstPrgCont> *Prg)
{
	//adds new program list
	BRenderPrg = true;
	Uninstlst = Prg;
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
	if(!(Uninstall.empty())) //if there is programs to uninstall
	{
		//execute every uninstallsring
		for(int i = 0 ; i < Uninstall.size(); ++i)
		{
			WMI->ExecMethod(Uninstall[i].Uninsstr);
		}
		std::vector<CUinstPrgCont> TempCont;
		//remove checked program from the list
		for(int i = 0; i < (*Uninstlst).size(); ++i)
		{
			if(!((*Uninstlst)[i].BChecked)) TempCont.push_back((*Uninstlst)[i]);
		}
		(*Uninstlst).erase((*Uninstlst).begin(), (*Uninstlst).end());
		(*Uninstlst) = TempCont;
		
		//reset counter
		PrgChkBox.ResetChecked();
	}

	//Run WMI for another computers in box
	if(!(CompNames.empty()))
	{
		CWMIRun *Others = new CWMIRun[CompNames.size()]; // create separate WMI objects
		for(int i = 0 ; i < CompNames.size(); ++i)
		{

			if(!(Uninstall.empty()))
			{
				//connect and run every uninstallstring
				for(int i = 0 ; i < Uninstall.size(); ++i)
				{
					Others[i].InsertLog(Log);
					Others[i].SecPrevAdded(true);
					Others[i].ConnectWMI(CompNames[i].Name);
					Others[i].ExecMethod(Uninstall[i].Uninsstr);
				}
			}

		}
		delete [] Others; // delete WMI objects
	}
}