#ifndef PrgSelector_h
#define PrgSelector_h

#include "ChkPrg.h"
#include "CompInfo.h"
#include "TCheckBoxCont.h"
#include "InputTextBox.h"

class CPrgSelector
{

public:

	void Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton);

	void SetWhereConnected(std::string Name);

	void Update();

	void HandleEvent(SDL_Event *e);

	void Render();

	void SetPrg(std::vector<CUinstPrgCont> *Prg);

private:

	CLog *Log;

	bool BRenderPrg;

	unsigned int NrCheckedPrg;

	CWMIRun *WMI;

	SDL_Color TxtColor;

	CTextHandler HowManyUninst;
	CTextHandler WhereConnected;
	CTextHandler WhereInstall;
	CInputTextBox IPBox;

	CButton Plus;
	CButton FromFile;
	CButton Begin;

	CCheckBoxCont<CUinstPrgCont> PrgChkBox;
	CCheckBoxCont<SCompInfo> CompChkBox;

	// pointer to programs list  
	std::vector<CUinstPrgCont> *Uninstlst;

	// container of computers where too must start uninstallation process
	std::vector<SCompInfo> CompNames;

	void BeginUninstall();
};

#endif