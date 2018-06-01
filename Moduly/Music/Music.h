#ifndef Music_h
#define Music_h

#include <SDL.h>
#include <string>
#include "Log.h"
#include <SDL_mixer.h>
#include <string>

class CMusic
{
public:
	// creates object and gives variables NULL values
	CMusic();
	
	//deallocate memory
	~CMusic();

	//Initialize object
	bool Init(CLog *TLog);

	//Load music from file
	bool Load(std::string SPath);

	//Play music
	void Play();

	//Pause music
	void Pause();

	//Stop Music
	void Stop();

	// returns true when music is stopped
	bool IsStoped();

	//returns true when music is paused
	bool IsPaused();

private:

	//Music that will be played 
	Mix_Music *MMusic;
	CLog *Log;
};


#endif