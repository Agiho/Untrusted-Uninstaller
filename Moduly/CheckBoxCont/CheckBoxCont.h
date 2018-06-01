#ifndef CheckBoxCont_h
#define CheckBoxCont_h

#include <SDL.h>
#include <memory>
#include <vector>
#include "Texture.h"
#include "UinstPrgCont.h"
#include "TextHandler.h"
#include "Slider.h"

class CCheckBoxCont
{

public:

	void Init(CLog *TLog, unsigned int WinW, unsigned int WintH, SDL_Renderer *Renderer, std::vector<CUinstPrgCont> *Programslst, std::string FontPath, std::shared_ptr<CTexture> SliderTex);

	void Render();

	void HandleEvent(SDL_Event *e);

	std::vector<CUinstPrgCont> GetChkPrograms();

	//void Update();


private:

	CLog *Log;
	SDL_Renderer *Renderer;

	unsigned int CurrentLine;

	unsigned int WinWidth, WinHeight; //Window size

	//std::shared_ptr<CTexture> Texture; 

	std::vector<SDL_Rect> Sqrs; //checkbox size and position

	SDL_Rect Frame; //main frame of this object 

	CSlider Slider;

	std::vector<CTextHandler> Names;

	std::vector<CUinstPrgCont> *Programs; //program and uninstall paths list

};

#endif