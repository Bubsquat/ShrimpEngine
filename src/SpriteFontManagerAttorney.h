// attorney class for spritefont manager

#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"	

class SpriteFontManagerAttorney
{
	friend class Game;

private:
	static void Terminate() { SpriteFontManager::Instance().privDelete(); };

};




#endif !_SpriteFontManagerAttorney
