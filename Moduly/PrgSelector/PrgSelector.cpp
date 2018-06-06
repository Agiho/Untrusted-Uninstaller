#include "PrgSelector.h"

void CPrgSelector::Init(CLog *TLog, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath,
	std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton, std::shared_ptr<CTexture> PlusButton)
{
	int ButH = 50;
	int ButW = 100;
	Log = TLog;

	SDL_Color C = {0,0,0};
	TxtColor = C;

	Plus.Init(ScrW - ButW, ButH , ButW/2, ButH, StdButton, ButW, 0, TLog, Render);
	FromFile.Init(ScrW - ButW*2, ButH*2, ButW, ButH, StdButton, 0,0, TLog, Render, "", "",FontPath);
	FromFile.SetCaption("Z Pliku");
	Begin.Init(ScrW - ButW - 10, ScrH - ButH - 10, ButW, ButH, StdButton,0,0, TLog, Render, "","", FontPath);
	Begin.SetCaption("Odinstaluj");
	
	SDL_Point Pos;
	Pos.x = 10;
	Pos.y = ScrH - ButH - 10;
	HowManyUninst.Init(Pos,FontPath, ButH -1,TLog, Render);
	HowManyUninst.LoadFromRenderedText("Programów do odinstalwania: 0", TxtColor);
	Pos.x = 10;
	Pos.y = ButH + 10;
	WhereConnected.Init(Pos,FontPath, ButH -1,TLog, Render);
	WhereConnected.LoadFromRenderedText("Pod³¹czony do: ", TxtColor);
	Pos.x = 10;
	Pos.y = ScrH - ButH - 10;
	WhereInstall.Init(Pos,FontPath, ButH -1,TLog, Render);
	WhereInstall.LoadFromRenderedText("Wykonaj Te¿ na:", TxtColor);
	SDL_Rect RectPos;
	RectPos.x = ScrW - ButW*2;
	RectPos.y = ButH;
	RectPos.w = ButW;
	RectPos.h = ButH;
	IPBox.Init(TLog, RectPos, FontPath, Render, TxtColor);

	
	PrgChkBox.Init(TLog, ScrW ,ScrH ,Render, Programslst, FontPath, FirstSlid);
}

void CPrgSelector::Update()
{

}

void CPrgSelector::HandleEvent(SDL_Event *e)
{

}

void CPrgSelector::Render()
{
	// textboxes and inputbox
	HowManyUninst.Render();
	WhereConnected.Render();
	WhereInstall.Render();
	IPBox.Render();

	//buttons
	Plus.Render();
	FromFile.Render();
	Begin.Render();

	//checkboxes
	PrgChkBox.Render();
}