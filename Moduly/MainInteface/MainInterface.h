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
#include "WMIRun.h"
#include "ChkPrg.h"
#include "RSrvStart.h"

//#include "Slider.h"

class MainInterface
{

public:

	void Init(CLog *TLog, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string Textures,  std::vector<CUinstPrgCont> *Programslst);

	void Render();

	void Update();

	void HandleEvent(SDL_Event *e);

	bool IsQuit();

private:

	enum Phases {

		LOCALCH = 0,
		GETIP = 1,
		MAIN = 2,
		ALL = 3


	};

	Phases Phase;

	ChkPrg Checker;
	CWMIRun RExec;

	CLog *Log;

	CFile Positions;

	std::vector<CUinstPrgCont> Programs;

	unsigned int ScrWidth , ScrHeight;

	bool BQuit;

	CTexturesMgr TexCont;

	//BUTTONS
	CButton Local;
	CButton Remote;


	void LoadPos(CLog *TLog, SDL_Renderer* Render, std::string Textures);
};

#endif