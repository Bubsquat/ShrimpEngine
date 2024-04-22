// patrol pattern that directs the tank towards the player 

#ifndef _PersuePatrolPattern
#define _PersuePatrolPattern

#include "PatrolPatternBase.h"

class PersuePatrolPattern : public PatrolPatternBase
{
public:

	PersuePatrolPattern() = default;
	PersuePatrolPattern(const PersuePatrolPattern&) = delete;
	PersuePatrolPattern& operator = (const PersuePatrolPattern&) = delete;
	~PersuePatrolPattern() {};

	const Vect GetNextPos(int& posNum, Vect pos);

private:

};


#endif _PersuePatrolPattern

