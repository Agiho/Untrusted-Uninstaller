#ifndef MsgBox_h
#define MsgBox_h

#include <SDL.h>
#include <string>
#include "Log.h"

class CMsgBox
{
public:

	CMsgBox();
	~CMsgBox();

	void IstertLog(CLog *TLog);

	void MakeOK();
	void MakeYesNo();
	void MakeCustom(const SDL_MessageBoxButtonData buttons[], int NrButtons);

	void CreateColorScheme(SDL_MessageBoxColor Background, SDL_MessageBoxColor Text, SDL_MessageBoxColor ButtonBorder, SDL_MessageBoxColor ButtonBackground, SDL_MessageBoxColor ButtonSelected);

	int ShowMsg(std::string Title, std::string Message);

private:

	CLog *Log;

	bool BTypeChoosed;

	bool BCreated;

	bool BColorDefined;

	int ButtonsNr;

	SDL_MessageBoxButtonData *Buttons;

	SDL_MessageBoxColorScheme ColorScheme;

	SDL_MessageBoxData MessageBoxData;

};

#endif