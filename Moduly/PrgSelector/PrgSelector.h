#ifndef PrgSelector_h
#define PrgSelector_h

#include <algorithm>
#include "ChkPrg.h"
#include "CompInfo.h"
#include "TCheckBoxCont.h"
#include "InputTextBox.h"
#include "BasicFileDialog.h"
#include "PrepUninst.h"
#include "ChkPrg.h"
#include "MsgBox.h"

class CPrgSelector
{

public:

	//initializes main window with programs and computers lists
	void Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton);

	// set text where program is curently connected
	void SetWhereConnected(std::string Name);

	// update functions for object that need it
	void Update();

	//handle events in main window
	void HandleEvent(SDL_Event *e);

	// render everything
	void Render();

	//set new program list to uninstallation
	void SetPrg(std::vector<CUinstPrgCont> *Prg);

private:

	//LOG
	CLog *Log;

	// file variable for reading computers list
	CFile File;

	//where connected
	std::string ConnectedTo;

	//there is need renderprglist (will be removed)
	bool BRenderPrg;

	//how many programs are checked
	unsigned int NrCheckedPrg;

	//pointer to WMI
	CWMIRun *WMI;

	//text color
	SDL_Color TxtColor;

	//text displayed 
	CTextHandler HowManyUninst;
	CTextHandler WhereConnected;
	CTextHandler WhereInstall;
	CInputTextBox IPBox;

	//buttons displayed in program selection screen
	CButton Plus;
	CButton FromFile;
	CButton Begin;

	//messagebox
	CMsgBox MsgYesNo;

	//need prepare some installations
	bool BNeedPrepare;

	//preparation for uninstallation class
	CPrepareUninst WPrepUninst;

	//programs and computers containers
	CCheckBoxCont<CUinstPrgCont> PrgChkBox;
	CCheckBoxCont<SCompInfo> CompChkBox;

	// pointer to programs list  
	std::vector<CUinstPrgCont> *Uninstlst;

	// container of computers where too must start uninstallation process
	std::vector<SCompInfo> CompNames;

	//reads stations names or ips from file
	void FileRead(std::string Path);

	//begins uninstall process
	void BeginUninstall(std::vector<CUinstPrgCont> Uninstall);
};

#endif