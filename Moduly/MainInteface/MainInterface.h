#ifndef MainInterface_h
#define MainInterface_h

#include <SDL.h>
#include <sstream>
#include "Texture.h"
#include "Button.h"
#include "Log.h"
#include "TexturesMgr.h"
#include "UinstPrgCont.h"
#include "TCheckBoxCont.h"
#include "UserAndIP.h"
#include "WMIRun.h"
#include "ChkPrg.h"
#include "RSrvStart.h"
#include "PrgSelector.h"

//#include "Slider.h"

class CMainInterface
{

public:

	//initialize interface, sets positions and initiates buttons
	void Init(CLog *TLog, ChkPrg *TChecker, CWMIRun *WMI, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string FontPath);

	//render interface
	void Render();

	//runs update functions for class which need it 
	void Update();

	// handle events in all program
	void HandleEvent(SDL_Event *e);

	// returns true need quit program
	bool IsQuit();

private:

	// states in maininterface to render and handle
	enum Phases {

		LOCALCH = 0,
		GETIP = 1,
		MAIN = 2,
		PRG_SELECT = 3,
		UNINST_STATUS = 4,
		ALL = 5

	};

	// variable for keep current phase
	Phases Phase;

	//pointers to checker registry and WMI
	ChkPrg *Checker;
	CWMIRun *RExec;

	CLog *Log;

	// variable file with buttonspositions 
	CFile Positions;

	// programs list
	std::vector<CUinstPrgCont> Programs;

	//screen width and height
	unsigned int ScrWidth , ScrHeight;

	//is need quit
	bool BQuit;

	//texture menager class and container
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

	CPrgSelector Select;

	//Private functions

	//loading buutons pos
	void LoadPos(CLog *TLog, SDL_Renderer* Render, int ID, std::string Font);

	//returns texture path for ID
	const char* GetTexbyID(int ID);
};

#endif