// patrol pattern that directs the tank towards the player 

#include "PersuePatrolPattern.h"
#include "PatrolPatternBase.h"
#include "LevelManager.h"

const Vect PersuePatrolPattern::GetNextPos(int&, Vect)
{
	Vect pos = LevelManager::GetPlayerLocation();

	return pos;
}
