#ifndef MainInterface_h
#define MainInterface_h

#include <SDL.h>
#include <sstream>
#include "Texture.h"
#include "Button.h"
#include "Log.h"
#include "TexturesMgr.h"
#include "UinstPrgCont.h"
#include "CheckBoxCont.h"
#include "UserAndIP.h"
#include "WMIRun.h"
#include "ChkPrg.h"
#include "RSrvStart.h"
#include "PrgSelector.h"

//#include "Slider.h"

class MainInterface
{

public:

	void Init(CLog *TLog, ChkPrg *TChecker, CWMIRun *WMI, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, 
		std::string Textures,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath);

	void Render();

	void Update();

	void HandleEvent(SDL_Event *e);

	bool IsQuit();

private:

	enum Phases {

		LOCALCH = 0,
		GETIP = 1,
		MAIN = 2,
		PRG_SELECT = 3,
		UNINST_STATUS = 4,
		ALL = 5

	};

	Phases Phase;

	ChkPrg *Checker;
	CWMIRun *RExec;

	CLog *Log;

	CFile Positions;

	std::vector<CUinstPrgCont> Programs;

	unsigned int ScrWidth , ScrHeight;

	bool BQuit;

	CTexturesMgr TexCont;

	//Login Info

	std::string IP;
	std::string USER;
	std::string PASSWORD;


	//BUTTONS
	CButton Local;
	CButton Remote;

	//SECTIONS
	CUserAndIP WAIWin;

	CCheckBoxCont PrgChkBox;

	CPrgSelector Select;

	//Private functions

	void LoadPos(CLog *TLog, SDL_Renderer* Render, int ID);

	const char* GetTexbyID(int ID);
};

#endif