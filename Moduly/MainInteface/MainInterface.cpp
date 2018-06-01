#include "MainInterface.h"

void MainInterface::Init(CLog *TLog, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string Textures, std::vector<CUinstPrgCont> *Programslst)
{
	Phase = LOCALCH;
	Log = TLog;
	ScrWidth = ScrW;
	ScrHeight = ScrH;
	TexCont.Init(Render, TLog);
	LoadPos(TLog, Render,Textures);
	CCheckBoxCont PrgChkBox;
	PrgChkBox.Init(TLog, ScrW ,ScrH ,Render, Programslst);

}

void MainInterface::Render()
{
	switch(Phase)
	{
	case LOCALCH:
		Local.Render();
		Remote.Render();
		break;

	case GETIP:

		break;
	}
} 

void MainInterface::Update()
{

}

void MainInterface::HandleEvent(SDL_Event *e)
{
	switch(Phase)
	{
	case LOCALCH:
		if(Local.HandleEvent(e));

		if(Remote.HandleEvent(e)) Phase = GETIP;

		break;

	case GETIP:

		break;
	}
}

bool MainInterface::IsQuit()
{
	return BQuit;
}

void MainInterface::LoadPos(CLog *TLog, SDL_Renderer* Render, std::string Textures)
{
	unsigned int FirstW = 100; //first 2 buttons width
	unsigned int FirstH = 50; //first 2 buttons height
	Local.Init(((ScrWidth/2) - FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(Textures.c_str()),0,TLog,Render);
	Remote.Init(((ScrWidth/2) + FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(Textures.c_str()),FirstW,TLog,Render);

}