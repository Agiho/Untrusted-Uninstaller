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
#include "UninstMgr.h"
#include "Terminator.h"
#include "ScriptRunner.h"
#include "FilesList.h"

class CPrgSelector
{

public:

	CPrgSelector();

	//initializes main window with programs and computers lists
	void Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton);

	// set text where program is curently connected
	void SetWhereConnected(std::string Name);

	//show filtered list
	void ShowFilter(std::string FilterWord);

	// sets pointer to uninstallation menager
	void SetUninstMgr(CUninstMgr *Mgr);

	// sets pointer to object  for terminate processes
	void SetTerminator(CTerminator *TTerminator);

	// sets pointer to script runner
	void SetScriptRunner(CScriptRunner *TScriptRunner);

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

	//is filter on
	bool BFilter;

	//how many programs are checked
	unsigned int NrCheckedPrg;

	//pointer to WMI
	CWMIRun *WMI;

	//uninstall menager
	CUninstMgr *UninstMgr;

	//process terminator
	CTerminator *Terminator;

	//script runner
	CScriptRunner *ScriptRunner;

	//text color
	SDL_Color TxtColor;

	//text displayed 
	CTextHandler HowManyUninst;
	CTextHandler WhereConnected;
	CTextHandler WhereInstall;
	CTextHandler IPInfo;
	CInputTextBox IPBox;
	CInputTextBox InputFilter;

	//buttons displayed in program selection screen
	CButton Plus;
	CButton FromFile;
	CButton Begin;
	CButton Filter;
	CButton Terminate;
	CButton SelectScript;

	//need prepare some installations
	bool BNeedPrepare;

	//true when show Process terminator Window
	bool BShowTerminator;

	//true when show Script Runner Window
	bool BShowScriptRunner;

	//preparation for uninstallation class
	CPrepareUninst WPrepUninst;

	//programs and computers containers
	CCheckBoxCont<CUinstPrgCont> PrgChkBox;
	CCheckBoxCont<SCompInfo> CompChkBox;

	// pointer to programs list  
	std::vector<CUinstPrgCont> *Uninstlst;

	//filtered list 
	std::vector<CUinstPrgCont> Filtered;
	std::vector<CUinstPrgCont*> FilterMainCon;

	// container of computers where too must start uninstallation process
	std::vector<SCompInfo> CompNames;

	//reads stations names or ips from file
	void FileRead(std::string Path);

	//begins uninstall process
	void BeginUninstall(std::vector<CUinstPrgCont> Uninstall);
};

#endif