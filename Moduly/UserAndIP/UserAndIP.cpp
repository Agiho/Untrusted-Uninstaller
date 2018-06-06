#include "UserAndIP.h"

void CUserAndIP::Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect PosButTex,
		unsigned int SCrW,  unsigned int SCrH, std::string Font)
{
	Log = TLog;
	Renderer = Render;

	Window.h = SCrH / 2;
	Window.w = SCrW / 2;
	Window.x = (SCrW / 2) - Window.w;
	Window.y = (SCrH / 2) - Window.h;

	SDL_Rect Position;
	int TxtHeight = 20;
	Position.x = Window.x + (Window.w / 2);
	Position.y = Window.y + (Window.h / 2) - TxtHeight - 10;
	Position.h = TxtHeight;
	Position.w = Window.w / 2;
	SDL_Color Col = { 0,0,0 };

	IP.Init(TLog, Position, Font, Render, Col, 15);
	IP.SetTxt("Brak IP");

	Position.y = Window.y + (Window.h / 2);
	User.Init(TLog, Position, Font, Render, Col, 15);
	User.SetTxt("Domyœlny u¿ytkownik");

	Position.y = Window.y + (Window.h / 2) + TxtHeight + 10;
	Password.Init(TLog, Position, Font, Render, Col, 15);
	Password.SetTxt("Domyœlne has³o");

	Position.y + TxtHeight + 10;
	LogIn.Init((Position.x + (Position.w / 2)) - PosButTex.w / 2, Position.y, PosButTex.w, PosButTex.h, TTexture, PosButTex.x, PosButTex.y,
		TLog, Render);
	LogIn.ChangeVis(true);
}

void CUserAndIP::Render()
{
	SDL_SetRenderDrawColor(Renderer, 222, 255, 255, 0); // white
	SDL_RenderFillRect(Renderer, &Window); //render filled rect
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0); //black
	SDL_RenderDrawRect(Renderer, &Window); //border

	IP.Render();
	User.Render();
	Password.Render();

	LogIn.Render();

}

bool CUserAndIP::HandleEvent(SDL_Event *e)
{
	//input into textboxes
	IP.Input(e);
	User.Input(e);
	Password.Input(e);

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