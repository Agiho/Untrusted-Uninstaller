#ifndef PrgSelector_h
#define PrgSelector_h

#include "ChkPrg.h"
#include "CheckBoxCont.h"
#include "InputTextBox.h"

class CPrgSelector
{

public:

	void Init(CLog *TLog, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton, std::shared_ptr<CTexture> PlusButton);

	void Update();

	void HandleEvent(SDL_Event *e);

	void Render();

private:

	CLog *Log;

	SDL_Color TxtColor;

	CTextHandler HowManyUninst;
	CTextHandler WhereConnected;
	CTextHandler WhereInstall;
	CInputTextBox IPBox;

	CButton Plus;
	CButton FromFile;
	CButton Begin;

	CCheckBoxCont PrgChkBox;

	CWMIRun *WMI;

	std::vector<CUinstPrgCont> *Uninstlst;
};

#endif