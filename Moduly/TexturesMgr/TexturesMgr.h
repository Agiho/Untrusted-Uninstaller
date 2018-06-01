#ifndef GameTextures_h
#define GameTextures_h

#include "Texture.h"
#include <string>
#include <vector>
#include <list>
#include <memory>

class CTexturesMgr
{

public:
	
	//initializesz class, needed for init function in texture class
	void Init(SDL_Renderer* Render, CLog* LogT);

	// returns pointer to texture
	std::shared_ptr<CTexture> LoadTex(const char *Text);

private:

	SDL_Renderer* Renderer; 
	CLog* Log;

	//containers with textures
	std::list<std::shared_ptr<CTexture>> LoadedTex;
	std::list<std::shared_ptr<CTexture>>::iterator LTIter;
};

#endif