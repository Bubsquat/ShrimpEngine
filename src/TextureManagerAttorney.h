// attorney for texture manager

#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
	friend class Game;
private:
	static void Terminate() { TextureManager::Instance().privDelete(); };
};



#endif _TextureManagerAttorney


