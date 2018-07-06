#ifndef Slider_h
#define Slider_h

#include "Texture.h"
#include "Button.h"
#include "TexturesMgr.h"

class CSlider
{

public:

	// sets position and initialize butons
	void Init(CLog *TLog, int Tx, int Ty, int Tw, int Th, int ButW, int ButH, int SliderW, int SliderH,
		std::shared_ptr<CTexture> Tex, int StartTextX, int StartTextY,
		SDL_Renderer* Render, std::string SSoundOn = "", std::string SSoundClick = "");

	//sets maximum value for slider
	void SetMaxVal(unsigned int Val);

	//sets current value for slider
	void SetVal(unsigned int Val);

	//render slider
	void Render();

	// udpates slider size
	void Update(unsigned int Val);

	//handle events for slider
	void HandleEvent(SDL_Event *e);

	// returns current value and maximum posiible value
	unsigned int GetCurValue();
	unsigned int GetMaxVal();

	// functions for manage visibility
	bool GetVis();
	void ChangeVis(bool BVis);

private:

	//function for handlig slider bar, sets value by position
	void Slide(SDL_Event *e);

	CLog * Log;

	//true when it is visible and vertical
	bool BVisible;
	bool Vertical;

	unsigned int CurValue; //current value
	unsigned int MaxValue; // maximum possible value
	double Size; //size of slider button
	unsigned int OverSizeJump; //jump by more values in container if there is more values than Slider Bar Size

	//position of whole slider object
	SDL_Rect SliderPos;

	//buttons
	CButton Less;
	CButton More;
	CButton Slider;

	//texture
	std::shared_ptr<CTexture> Textures;

	//slider bar position and size
	SDL_Rect Bar;
	SDL_Point BarPos;
};

#endif
