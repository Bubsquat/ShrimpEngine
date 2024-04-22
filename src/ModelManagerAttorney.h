// model manager attorney

#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
	friend class Game;

private:
	static void Terminate() { ModelManager::Instance().privDelete(); };
};

#endif _ModelManagerAttorney