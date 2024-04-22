// patrol pattern where the tank will proceed down a list of waypoints and loop back to the first one

#ifndef _PatrolPatternWaypointLoop
#define _PatrolPatternWaypointLoop

#include "PatrolPatternBase.h"
#include <list>
#include "AzulCore.h"

class PatrolPatternWaypointLoop : public PatrolPatternBase
{
public:

	PatrolPatternWaypointLoop();
	PatrolPatternWaypointLoop(const PatrolPatternWaypointLoop&) = delete;
	PatrolPatternWaypointLoop& operator=(const PatrolPatternWaypointLoop&) = delete;
	~PatrolPatternWaypointLoop() = default;

	const Vect GetNextPos(int& posNum, Vect pos);

	enum PATTERNTYPE
	{
		CIRCLE, // didnt write this one yet
		LINE,
		DIAMOND,
		ZIGZAG,
		ARC // didnt write this one either
	};

	void GeneratePattern(float startPosX, float startPosZ, float pointDistance, PATTERNTYPE pat, int numPoints = -1);
	void AddCustomPattern(std::list<Vect>&);
	void SetMinimumDistance(float dist);

private:

	std::list<Vect> currentPattern;
	const float tankPlane = 40.0f;
	int curMaxPoints;
	float minDistance = 500.0f;
};

#endif _PatrolPatternWaypointLoop
