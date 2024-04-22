// attorney for shader manager

#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
	friend class Game;
private:
	static void Terminate() { ShaderManager::Instance().privDelete(); };
};


#endif _ShaderManagerAttorney
