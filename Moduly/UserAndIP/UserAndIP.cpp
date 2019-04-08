#include "UserAndIP.h"

void CUserAndIP::Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect PosButTex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font)
{
	Log = TLog;
	BShowUserPass = false;
	Renderer = Render;

	//sets window position
	Window.h = SCrH / 2;
	Window.w = SCrW / 2;
	Window.x = (SCrW / 2) - Window.w/2;
	Window.y = (SCrH / 2) - Window.h/2;

	// sets tesxboxes
	SDL_Rect Position;
	int TxtHeight = 20;
	Position.x = Window.x + (Window.w / 4);
	Position.y = Window.y + (Window.h / 2) - TxtHeight - 10;
	Position.h = TxtHeight;
	Position.w = Window.w / 2;
	SDL_Color Col = { 0,0,0 };

	IP.Init(TLog, Position, Font, Render, Col, 15);
	IP.SetTxt("");

	SDL_Point PPos = { Position.x - 70, Position.y};
	IPDescrip.Init(PPos,Font, 15, TLog, Render);
	IPDescrip.LoadFromRenderedText("Adres IP:", Col);

	Position.y = Window.y + (Window.h / 2);
	User.Init(TLog, Position, Font, Render, Col, 15);
	User.SetTxt("Domniemany");

	PPos.x = Position.x - 85;
	PPos.y = Position.y;
	UserDescrip.Init(PPos,Font, 15, TLog, Render);
	UserDescrip.LoadFromRenderedTextUnicode(L"U¿ytkownik:", Col);

	Position.y = Window.y + (Window.h / 2) + TxtHeight + 10;
	Password.Init(TLog, Position, Font, Render, Col, 15);
	Password.SetTxt("Domniemane");
	Password.Hide(true);

	PPos.x = Position.x - 50;
	PPos.y = Position.y;
	PassDescrip.Init(PPos,Font, 15, TLog, Render);
	PassDescrip.LoadFromRenderedTextUnicode(L"Has³o:", Col);

	//set buttons

	ShowUserPass.Init((Position.x + ((Position.w/3) / 2)) - 20 -  PosButTex.w / 2, Window.y + (Window.h / 2) + 10, PosButTex.w, PosButTex.h, TTexture, PosButTex.x, PosButTex.y,
		TLog, Render,"","", Font);
	ShowUserPass.ChangeVis(true);
	ShowUserPass.SetDiam(PosButTex.w*3, PosButTex.h);
	ShowUserPass.SetCaption("Edytuj dane logowania");

	Position.y = Position.y + TxtHeight + 20;
	LogIn.Init((Position.x + (Position.w / 2)) - PosButTex.w / 2, Position.y, PosButTex.w, PosButTex.h, TTexture, PosButTex.x, PosButTex.y,
		TLog, Render,"","", Font);
	LogIn.ChangeVis(true);
	LogIn.SetCaption("Zaloguj");

	//activation first inputbox
	IP.ChangeActiv(true);
}

void CUserAndIP::Render()
{
	//Window
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // color
	SDL_RenderFillRect(Renderer, &Window); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Window); //border

	//texts
	IPDescrip.Render();
	if(BShowUserPass) // when user want to show this fields
	{
		UserDescrip.Render();
		PassDescrip.Render();
	}

	//inputboxes
	IP.Render();
	if(BShowUserPass) // when user want to show this fields
	{
		User.Render();
		Password.Render();
	}
	else ShowUserPass.Render();

	//button
	LogIn.Render();

}

bool CUserAndIP::HandleEvent(SDL_Event *e)
{
	//input into textboxes
	auto BChoice = IP.Input(e);
	if(BChoice == SDLK_TAB)
	{
		IP.ChangeActiv(false);
		if(BShowUserPass) User.ChangeActiv(true);// when user want to show this fields
		return false;
	}
	else if(BChoice == SDLK_RETURN) return true;

	if(BShowUserPass) 
	{
		BChoice = User.Input(e);
		if(BChoice == SDLK_TAB)
		{
			User.ChangeActiv(false);
			Password.ChangeActiv(true);
			return false;
		}
		else if(BChoice == SDLK_RETURN) return true;

		BChoice = Password.Input(e);
		if(BChoice == SDLK_TAB)
		{
			Password.ChangeActiv(false);
			IP.ChangeActiv(true);
			return false;
		}
		else if(BChoice == SDLK_RETURN) return true;
	}
	else
	{
		if(ShowUserPass.HandleEvent(e)) 
		{
			ShowUserPass.ChangeVis(false);
			BShowUserPass = true;
			User.ChangeActiv(true);
		}
	}

	//only if button clicked returns true
	return LogIn.HandleEvent(e);
}

std::string CUserAndIP::GetIP()
{
	return IP.GetText();
}

std::string CUserAndIP::GetUser()
{
	return User.GetText();
}

std::string CUserAndIP::GetPassword()
{
	return Password.GetText();
}