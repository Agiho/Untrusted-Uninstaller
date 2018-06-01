#include "SFX.h"

CSFX::CSFX()
{
	Log = nullptr;
	MSound = NULL;
}
// free allocated memory
CSFX::~CSFX()
{
	Mix_FreeChunk(MSound);
	MSound = NULL;
	Log = nullptr;
}

void CSFX::Init(CLog *TLog)
{
	Log = TLog;
}

bool CSFX::Load(std::string SPath)
{
		//Load sound effects
		MSound = Mix_LoadWAV( SPath.c_str());
		if( MSound == NULL )
		{
			//stream and string for error information
			std::stringstream Stream;
			Stream.str("");
			std::string SErrString;
			Stream << "Failed to load sound effect! " << SPath.c_str() <<" SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
			Log->WriteTxt(Stream.str());
		}
	return true;
}

// Play sound
void CSFX::Play()
{
	Mix_PlayChannel( -1, MSound, 0);
}

// free allocated memory
void CSFX::Free()
{
	Mix_FreeChunk(MSound);
	MSound = NULL;
}