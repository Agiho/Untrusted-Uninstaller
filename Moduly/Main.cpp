#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <time.h>
#include "Log.h"
#include "Music.h"
#include "Button.h"
#include "ChkPrg.h"
#include "WMIRun.h"
#include "Window.h"
#include "Texture.h"
#include "MainInterface.h"


int main(int argc, char *argv[])
{
	std::stringstream File;
	File << "C:/Temp/Log"<< time(NULL) << ".txt";
	CLog Log(File.str());
	ChkPrg Checker;
	CWMIRun RExec;
	Checker.InstgertLog(&Log);
	RExec.InsertLog(&Log);
	
	CMainInterface Main;
	
	//pointer to renderer
	SDL_Renderer* pRenderer;
	//Creating Window and initialize it
	CWindow MainWindow("Untrusted Uninstaller",&Log, 960, 720, SDL_WINDOW_SHOWN);
	
	MainWindow.Init();
	//RExec.ConnectWMI();
	//Getting pointer to renderer
	pRenderer = MainWindow.GetRenderer();

	//Music object and initialization
	CMusic Music;
	Music.Init(&Log);

	//events (Keyboard mause etc).
	SDL_Event e;
	{
		
	Main.Init(&Log, &Checker, /*&RExec,*/ pRenderer, 960,720,"PostFont.ttf");

	auto BQuit = false;
	
	//Main loop
	while(!BQuit)
	{
		//clear window
		MainWindow.ClearScr(222,255,255,0);

		if(Main.IsQuit())  BQuit = true;

		Main.Update();

		Main.Render();

		//show renderer object in window
		MainWindow.UpdateScr();

		//Handle events on queue 
		while( SDL_PollEvent( &e ) != 0 ) 
		{ 
			//User requests quit 
			if( e.type == SDL_QUIT )  BQuit = true;  
			Main.HandleEvent(&e);
		}
		
	}
	}
	Log.WriteTxt("Program Closed");

	//MainWindow.Close();

	//Log.~CLog();
	//END
	return 0;
}