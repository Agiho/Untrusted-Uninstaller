#ifndef Terminator_h
#define Terminator_h

#include <SDL.h>
#include "InputTextBox.h"
#include "TCheckBoxCont.h"
#include "Button.h"
#include "ProcessInfo.h"
#include "WMIRun.h"

class CTerminator
{

public:

	void Init(CLog *TLog, SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH
		, std::string FontPath);

	void AddProcesses(std::vector<std::string> ProcNames);
	void AddOne(std::string ProcName);
	void ClrLst();

	std::vector<std::string> GetProcesses();

	void Activate();
	bool IsActive();

	void Terminate(CWMIRun *WMI);
	void Terminate(CWMIRun *WMI, std::vector<std::string> ProcNames);

	bool HandleEvent(SDL_Event *e);

	void Render();

private:

	CLog *Log;

	SDL_Renderer *Renderer;

	bool BActive;

	CButton Plus;
	CButton OK;

	CTextHandler Descr;
	CTextHandler Descr2;


	CInputTextBox InputBox;

	std::vector<SProcessInfo> Processes;

	CCheckBoxCont<SProcessInfo> ChkBoxCont;

	SDL_Rect Window;
};

#endif