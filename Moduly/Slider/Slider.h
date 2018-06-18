#ifndef Slider_h
#define Slider_h

#include "Texture.h"
#include "Button.h"
#include "TexturesMgr.h"

class CSlider
{

public:

	void Init(CLog *TLog, int Tx, int Ty, int Tw, int Th, int ButW, int ButH, int SliderW, int SliderH,
		std::shared_ptr<CTexture> Tex, int StartTextX, int StartTextY,
		SDL_Renderer* Render, std::string SSoundOn = "", std::string SSoundClick = "");

	void SetMaxVal(unsigned int Val);

	void SetVal(unsigned int Val);

	void Render();

	void Update(unsigned int Val);

	void HandleEvent(SDL_Event *e);

	unsigned int GetCurValue();
	unsigned int GetMaxVal();

	bool GetVis();
	void ChangeVis(bool BVis);

private:

	void Slide(SDL_Event *e);

	CLog * Log;

	bool BVisible;
	bool Vertical;

	unsigned int CurValue;
	unsigned int MaxValue;
	unsigned int Size;

	SDL_Rect SliderPos;

	CButton Less;
	CButton More;
	CButton Slider;
	std::shared_ptr<CTexture> Textures;
	SDL_Rect Bar;
	SDL_Point BarPos;
	//std::shared_ptr<CTexture> TButtonsTexture
};

#endif
