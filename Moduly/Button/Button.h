#ifndef Button_h
#define Button_h

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>
#include "SFX.h"
#include "Log.h"
#include "Texture.h"
#include "TextHandler.h"


class CButton
{
public:

	CButton(/*SDL_Renderer* Render,  CLog *TLog */);
	~CButton();

	void Init(int Tx, int Ty, int Tw, int Th, std::shared_ptr<CTexture> TButtonsTexture, int IButtonX, int IButtonY, CLog *TLog, SDL_Renderer* Render, std::string SSoundOn= "", std::string SSoundClick = "", std::string FontPath = "");

	// Set position of button
	void SetPos(int Tx, int Ty, int Tw = NULL, int Th = NULL);

	// Handle mouse and joystick events
	bool HandleEvent(SDL_Event *e);

	//shows button
	void Render();

	// setting diamesnos of button
	void SetDiam(int W, int H);

	//returns diamensons of button
	int GetHeight();
	int GetWidth();

	//PLaying sound
	void SoundOn();
	void SoundDown();

	//caption setting and retriving options
	void SetCaption(std::string Cap);
	std::string GetCaption();

	//Change states of button
	void StateOut();
	void StateOn();
	void StateDown();
	void Active(bool active);
	bool IsActive();
	
	//chcanging and check visibility
	void ChangeVis(bool BVis);
	bool ChangeVis();
	bool GetVis();


private:
	
	//button states
	enum BState
	{
		B_Out = 0,
		B_On = 1,
		B_Down = 2,
		B_Total = 3
	};

	//is button active
	bool BActive;

	//caption writen on button
	std::string Caption;
	bool FontInit;
	std::string PathFont;

	// CaptionHandler
	CTextHandler CaptionH;

	//sounds of button
	// mause on
	CSFX SM_On;
	//button down
	CSFX SM_Down;

	//true if is sound efect on mouse on and button down
	bool BSO, BSD;

	//Log file
	CLog *Log;

	// renderer pointer
	SDL_Renderer* Renderer;

	//Button properties
	int IWidth;
	int IHeight;
	SDL_Point PPos;

	//true when button is down
	//bool BClicked;

	//true when its not visible
	bool BVisible;

	//button texture
	std::shared_ptr<CTexture> TButton;

	//Current button state
	BState State;

	//Clips of button
	SDL_Rect RClips[B_Total];
};

#endif