#include "Music.h"

CMusic::CMusic()
{
	MMusic = NULL;	
}

CMusic::~CMusic()
{
	//free music and memory
	Mix_FreeMusic(MMusic);
	MMusic = NULL;
	Log = nullptr;
}

bool CMusic::Init(CLog *TLog)
{
	Log = TLog;
		// initialize music properties and format(initialize SDL_mixer)
		if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2 , 2048) < 0 )
		{
			//stream and string for error information
			std::stringstream Stream;
			Stream.str("");
			std::string SErrString;
			Stream << "SDL_Mixer couldn't be initialized SDL Error: \n" << Mix_GetError() << "\n";
			Log->WriteTxt(Stream.str());
			
		}
	return true;
}

bool CMusic::Load(std::string SPath)
{
	
		//Load Music from file
		MMusic = Mix_LoadMUS( SPath.c_str() );
		if( MMusic == NULL)
		{
			//stream and string for error information
			std::stringstream Stream;
			Stream.str("");
			std::string SErrString;
			Stream << "Cannot load music SDL_mixer error: \n" << Mix_GetError() << "\n";
			Log->WriteTxt(Stream.str());

		}
	return true;
}

void CMusic::Play() 
{
	//If there is no music playing
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( MMusic, -1 );
	}
	//If music is being played
	else
	{
		//If the music is paused
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
	}
}

void CMusic::Pause()
{
	if(Mix_PausedMusic() != 1)
	{
		//Pause the music
		Mix_PauseMusic();
	}
}

void CMusic::Stop()
{
	//Stop the music
	Mix_HaltMusic();
}

bool CMusic::IsStoped()
{
	if( Mix_PlayingMusic() == 0 )
	{
		return true;
	}
	return false;
}

bool CMusic::IsPaused()
{
	if( Mix_PausedMusic() == 1 )
	{
		return true;
	}
	return false;
}