// attorney for the game singleton 

#ifndef _GameAttorney
#define _GameAttorney

#include "Game.h"
class VisualizerDrawCmdBase;

class GameAttorney
{
	friend class TimeManager;
	friend class FreezeTime;

public:


private:

	static float GetTime() { return Game::Instance().GetTimeInSeconds(); };

};


#endif _GameAttorney
