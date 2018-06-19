#ifndef PrepareUninst_h
#define PrepareUninst_h

#include <vector>
#include "Button.h"
#include "UinstPrgCont.h"
#include "InputTextBox.h"


class CPrepareUninst
{

public:

	void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect Posbyttex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font);

	void CheckPrg(std::vector<CUinstPrgCont> Cont);

	std::vector<CUinstPrgCont> GetPrg();

	bool AllOK();

	void Render();

	void HandleEvent(SDL_Event *e);

private:

	CLog * Log;

	SDL_Renderer *Renderer;

	SDL_Rect Window;

	//text descrition
	CTextHandler Descrition; 
	CTextHandler PrgName;

	//textbox
	CInputTextBox Parameters;;

	CButton Next;

	bool BOK;

	SDL_Color TxtColor;

	std::vector<CUinstPrgCont> ClearStr;

	//programs with wrong uninstall string
	std::vector<CUinstPrgCont> ToDo;

	int Element;

};

#endif