// preprogrammed patrol pattern for the tank AI base clase

#ifndef _PatrolPatternBase
#define _PatrolPatternBase

class Vect;

class PatrolPatternBase
{
public:

	PatrolPatternBase() = default;
	PatrolPatternBase(const PatrolPatternBase&) = delete;
	PatrolPatternBase& operator = (const PatrolPatternBase&) = delete;
	virtual ~PatrolPatternBase() {};

	virtual const Vect GetNextPos(int &posNum, Vect pos) = 0;
	/* 
	Okay so if I forget this is gunna work by having an array of XZpos 
	that the ai controller is gunna call get next on and it will always return the next 
	one and the patrol pattern itself will handle giving the next position query kinda like a fsm 
	there patrol pattern for actually searching for the player will be in the tank controller and 
	called every so often as it moves from one way point to the next using the patrol pattern
	Also use euclidean distance squared to like do the pathfinds,
	find obstacles with collision system and have a preprogrammed dumb turn and try again 
	*/

};



#endif _PatrolPatternBase
