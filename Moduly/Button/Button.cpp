#include "Button.h"

CButton::CButton(/*SDL_Renderer* Render, CLog *TLog*/)
{
	//Default values
	Log = NULL;
	BVisible = true;
	PPos.x = 0;
	PPos.y = 0;
	State = B_Out;
	BSO = false;
	BSD = false;
	BActive = true;
	FontInit = false;
	Caption = " ";
}

// Free memory
CButton::~CButton()
{
	//TButton->Free();
	Log = nullptr;
}

// Initialize variables
void CButton::Init(int Tx, int Ty, int Tw, int Th, std::shared_ptr<CTexture> TButtonsTexture, int IButtonX, int IButtonY, CLog *TLog, SDL_Renderer* Render, std::string SSoundOn, std::string SSoundClick, std::string FontPath)
{
	Log = TLog;
	Renderer = Render;
	PPos.x = Tx;
	PPos.y = Ty;
	IWidth = Tw;
	IHeight = Th;
	TButton = TButtonsTexture;
	TButton->Init(Render, TLog);
	SM_On.Init(TLog);
	SM_Down.Init(TLog);
	if (SSoundOn != "")
	{
		SM_On.Load(SSoundOn);
		BSO = true;

	}
	if (SSoundClick != "")
	{
		SM_Down.Load(SSoundClick);
		BSD = true;

	}

	if (!(BSO && BSD))
	{
		Log->WriteTxt("Unable to load buttons sounds \n");
	}

	//Set sprites
	for (int i = 0; i < B_Total; ++i)
	{
		RClips[i].x = IButtonX;
		RClips[i].y = IButtonY + (i * IHeight);
		RClips[i].w = IWidth;
		RClips[i].h = IHeight;
	}

	FontInit = false;
	if (FontPath != "")
	{	
		SDL_Point Point;
		int Size = Th / 2;
		Point.x = PPos.x + (Tw / 2);
		Point.y = PPos.y + (Th / 2) - Size / 2;
		CaptionH.Init(Point, FontPath, Size, TLog, Render);
		FontInit = true;
	}
}

// Setting topleft point of button
void CButton::SetPos(int Tx, int Ty, int Tw, int Th)
{
	PPos.x = Tx;
	PPos.y = Ty;
	if(Tw) IWidth = Tw;
	if(Th) IHeight = Th;
}

bool CButton::HandleEvent(SDL_Event *e)
{
	bool BClicked = false;
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mause position
		int X, Y;
		SDL_GetMouseState(&X, &Y);

		//Check if mouse is inside button
		bool BInside = true;
		//Mouse is left of the button
		if( X < PPos.x )
		{
			BInside = false;
		}
		//Mouse is right of the button
		else if( X > PPos.x + IWidth )
		{
			BInside = false;
		}
		//Mouse above the button
		else if( Y < PPos.y )
		{
			BInside = false;
		}
		//Mouse below the button
		else if( Y > PPos.y + IHeight )
		{
			BInside = false;
		}
		//Mouse is outside button
		if( !BInside )
		{
			State = B_Out;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				// When mouse is on button
				case SDL_MOUSEMOTION:
					//Playing saound and set state
					if(State == B_Out) if(BSO) SM_On.Play();
					// setting state
					State = B_On;
					return BClicked;
			
				//When button is clicked
				case SDL_MOUSEBUTTONDOWN:

					//Playeing saound and set state
					if(BSD) SM_Down.Play();
					// setting state
					State = B_Down;
					BClicked = true;
					return BClicked;
				
			/*	case SDL_MOUSEBUTTONUP:
				State = B_Out;
				return BClicked;  */
			}
		}
	}
	return BClicked;
}

void CButton::Render()
{
	//Render curent state button texture 
	TButton->Render( PPos.x, PPos.y, &RClips[ State ] );
	if(FontInit)CaptionH.Render();
}

void CButton::SetDiam(int W, int H)
{
	IWidth = W;
	IHeight = H;
}

int CButton::GetHeight()
{
	return IHeight;
}

int CButton::GetWidth()
{
	return IWidth;
}

void CButton::SoundOn()
{
	//Playeing saound and set state
	if(BSO) SM_On.Play();
}
void CButton::SoundDown()
{
	//Playeing saound and set state
	if(BSD) SM_Down.Play();
}

void CButton::SetCaption(std::string Cap)
{
	Caption = Cap;
	SDL_Color Col = { 0,0,0 };
	//Set Text to render
	CaptionH.LoadFromRenderedText(Caption, Col);
	SDL_Point Point;
	//Calculating text position starting point
	Point.x = PPos.x + (IWidth / 2) - CaptionH.GetWidth() /2 ;
	Point.y = PPos.y + (IHeight / 2) - (CaptionH.GetHeight() / 2);
	CaptionH.SetPos(Point);
}
std::string CButton::GetCaption()
{
	return Caption;
}

void CButton::StateOut()
{
	State = B_Out;
}

void CButton::StateOn()
{
	State = B_On;
}

void CButton::StateDown()
{
	State = B_Down;
}

void CButton::Active(bool active)
{
	BActive = active;
}
bool CButton::IsActive()
{
	return BActive;
}

void CButton::ChangeVis(bool BVis)
{
	BVisible = BVis;
}
bool CButton::ChangeVis()
{
	return BVisible = !BVisible;
}
bool CButton::GetVis()
{
	return BVisible;
}