#ifndef CSFX_h
#define CSFX_h

#include <SDL.h>
#include <string>
#include <sstream>
#include "Log.h"
#include <SDL_mixer.h>

class CSFX
{
public:

	CSFX();
	~CSFX();

	//Initialize Log file
	void Init(CLog *TLog);

	//Load sound from file
	bool Load(std::string SPath);

	//Play sound
	void Play();

	//free memory
	void Free();

private:

	//sound
	Mix_Chunk *MSound;
	//Log class
	CLog *Log;
};
#endif