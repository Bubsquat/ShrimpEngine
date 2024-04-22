// patrol pattern where the tank will proceed down a list of waypoints and loop back to the first one

#include "PatrolPatternWaypointLoop.h"
#include <assert.h>
#include "../DataLogger.h"

PatrolPatternWaypointLoop::PatrolPatternWaypointLoop()
{
	curMaxPoints = 0;
}

const Vect PatrolPatternWaypointLoop::GetNextPos(int& posNum, Vect pos)
{

	//DataLogger::Add("distToPoint %f", distToPoint);
	//DebugMsg::out("distToPoint : %f\n", distToPoint);

	assert(curMaxPoints != 0);

	auto it = currentPattern.begin();
	Vect point;
	std::advance(it, posNum); // double check this
	
	point = *it;
	
	float distSquared = ((point.X() - pos.X()) * (point.X() - pos.X())) + ((point.Z() - pos.Z()) * (point.Z() - pos.Z()));
	
	//DebugMsg::out("distToPoint : %f targetDist : %f targetPointNum : %i\n", distSquared, minDistance*minDistance, posNum);


	if (distSquared >= minDistance*minDistance )
	{
		it = currentPattern.begin();
		std::advance(it, posNum); // double check this
		point = *it;
	}
	else if (distSquared < minDistance*minDistance)
	{
		posNum++;
		if (posNum >= curMaxPoints) posNum = 1;
		it = currentPattern.begin();
		std::advance(it, posNum);
		point = *it;
	}

	return point;

}


void PatrolPatternWaypointLoop::GeneratePattern(float startPosX, float startPosZ, float pointDistance, PATTERNTYPE patternType, int numPoints)
{

	switch (patternType)
	{

	case PATTERNTYPE::DIAMOND:

		currentPattern.push_back(Vect(startPosX, tankPlane, startPosZ));
		currentPattern.push_back(Vect(startPosX + pointDistance, tankPlane, startPosZ + pointDistance));
		currentPattern.push_back(Vect(startPosX, tankPlane, startPosZ + 2 * pointDistance));
		currentPattern.push_back(Vect(startPosX - pointDistance, tankPlane, startPosZ + pointDistance));

		curMaxPoints = 4;

		break;

	case PATTERNTYPE::LINE:

		assert(numPoints != -1);

		curMaxPoints = numPoints;

		for (int i = 0; i < numPoints; i++)
		{
			currentPattern.push_back(Vect(startPosX + i * pointDistance, tankPlane, startPosZ + i * pointDistance));
		}

		break;

	case PATTERNTYPE::ZIGZAG:

		assert(numPoints != -1);

		curMaxPoints = numPoints;

		for (int i = 0; i < numPoints; i++)
		{

			if (i % 2 == 0)
			{
				currentPattern.push_back(Vect(startPosX + i * pointDistance, tankPlane, startPosZ + i * pointDistance));
			}
			else
			{
				currentPattern.push_back(Vect(-startPosX + i * pointDistance, tankPlane, startPosZ + i * pointDistance));
			}

		}
		break;
	}

}

void PatrolPatternWaypointLoop::AddCustomPattern(std::list<Vect>& newPattern)
{
	currentPattern = newPattern;
}

void PatrolPatternWaypointLoop::SetMinimumDistance(float dist)
{
	minDistance = dist;
}