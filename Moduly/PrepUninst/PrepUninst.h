#ifndef PrepareUninst_h
#define PrepareUninst_h

#include <vector>
#include "Button.h"
#include "UinstPrgCont.h"
#include "InputTextBox.h"


class CPrepareUninst
{

public:

	//prepare window box and other object for event handling
	void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect Posbyttex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font);

	//checks program in container do they need special parameters
	void CheckPrg(std::vector<CUinstPrgCont> Cont);

	// returns program list which shoudl can be uninstalled without problems
	std::vector<CUinstPrgCont> GetPrg();

	// ist all programs ok
	bool AllOK();

	// render windows
	void Render();

	// get parameters from user to uninstall path 
	void HandleEvent(SDL_Event *e);

private:

	CLog * Log;

	SDL_Renderer *Renderer;

	// window borders
	SDL_Rect Window;

	//text descrition
	CTextHandler Descrition; 
	CTextHandler PrgName;

	//textbox
	CInputTextBox Parameters;;

	//next button
	CButton Next;

	bool BOK;

	// font color
	SDL_Color TxtColor;

	// programs with correct uninstall string
	std::vector<CUinstPrgCont> ClearStr;

	//programs with wrong uninstall string
	std::vector<CUinstPrgCont> ToDo;

	//nr of element currently need be corrected
	int Element;

};

#endif