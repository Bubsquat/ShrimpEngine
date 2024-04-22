// singleton manager for handling total and frame time 

#include "TimeManager.h"
#include "GameAttorney.h"
#include "FreezeTime.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
{
	pFreezeTime = new FreezeTime;
	previousTime = 0.0f;
	currentTime = 0.0f;
	frameTime = 0.0f;
}

TimeManager::~TimeManager()
{
	delete pFreezeTime;
}

void TimeManager::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

float TimeManager::privGetTime()
{
	return currentTime;
}

float TimeManager::privGetFrameTime()
{
	return frameTime;
}

void TimeManager::privProcessTime()
{	
	previousTime = currentTime;
	//currentTime = GameAttorney::GetTime(); // toggle freeze frame mode here
	currentTime = pFreezeTime->ComputeGameTime(previousTime);
	frameTime = currentTime - previousTime;
}
