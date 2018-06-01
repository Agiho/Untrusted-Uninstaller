#include "TexturesMgr.h"

void CTexturesMgr::Init(SDL_Renderer* Render, CLog* LogT)
{
	Renderer = Render;
	Log = LogT;	
}

std::shared_ptr<CTexture> CTexturesMgr::LoadTex(const char *Text) 
{
	std::string SCheck = Text;
	
	//checking if there is no textures yet
	
	if(LoadedTex.empty())
	{
		//creating texture
		auto TempTex = std::make_shared<CTexture>();
		TempTex->Init(Renderer, Log);
		try
		{
			//if texture doesn't load
			TempTex->Load(Text);
		}
		catch(std::string Err)
		{
			throw Err;
		}
		// oushing texture to list
		LoadedTex.push_back(TempTex);
		
		//returning pointer to object
		return LoadedTex.front();
	
	}
	else
	{
		
		//updating allobjects and allplatforms
		for(LTIter = LoadedTex.begin(); LTIter != LoadedTex.end(); LTIter++)
		{
			if( SCheck == (*LTIter)->GetPath())
			{
				//returning pointer to object
				return (*LTIter);
			}			
		}
		//creating texture object
		auto TempTex = std::make_shared<CTexture>();
		TempTex->Init(Renderer, Log);
		TempTex->Load(Text);
		//pushing to end new texture
		LoadedTex.push_back(TempTex);
		//returning adress to texture
		return LoadedTex.back();
	}	
}