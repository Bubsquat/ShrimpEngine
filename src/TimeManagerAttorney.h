// attorney for singleton time manager

#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
private:
	friend class Game;

	static void Terminate() { TimeManager::Terminate(); };
	static void ProcessTime() { TimeManager::Instance().privProcessTime(); };

};



#endif _TimeManagerAttorney
