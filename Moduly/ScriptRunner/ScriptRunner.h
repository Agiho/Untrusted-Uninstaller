#ifndef ScriptRunner_h
#define ScriptRunner_h

#include <SDL.h>
#include <Windows.h>
#include "InputTextBox.h"
#include "TCheckBoxCont.h"
#include "Button.h"
#include "ScriptInfo.h"
#include "WMIRun.h"
#include "MsgBox.h"
#include "FilesList.h"

class CScriptRunner
{

public:

	//initialize object
	void Init(CLog *TLog, SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH
		, std::string MainLoc , std::string FontPath); 

	void Activate(); // Set BActive value to true
	bool IsActive(); //return BActive value

	void AddCred(std::string TUser = "", std::string SPass = ""); // sets not default login and password

	void RunScript(std::vector<std::string> Where); // Runs checked scripts on computers in first parameter 

	bool HandleEvent(SDL_Event *e); // handle mause events

	void Render(); // render Window

	bool IsStarted(); // returns BStarted value
	void SetNotStarted(); //Sets BStarted to false

private:

	CLog *Log; // log pointer

	SDL_Renderer *Renderer; //pointer to SDL Renderer

	std::string User, Pass; // login data

	bool BActive; //true when window shoudl be rendered and active
	bool BStarted; // true when scripts already been launched

	CButton OK; //ok button

	//render text description
	CTextHandler Descr;
	CTextHandler Descr2; 

	std::vector<SScriptInfo> ScriptNfo; // all scripts

	CCheckBoxCont<SScriptInfo> ChkBoxCont; //checkbox with diles names

	std::vector<SScriptInfo> ScriptLaunch; //selected scripts

	SDL_Rect Window; //size of Window with scripts

};

#endif