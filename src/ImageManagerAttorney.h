// image manager attorney

#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
	friend class Game;

private:
	static void Terminate() { ImageManager::Instance().privDelete(); };
};

#endif _ModelManagerAttorney