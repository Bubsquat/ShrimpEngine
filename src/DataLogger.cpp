// singleton dev tool for writing data to the screen 

#include "DataLogger.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"
#include "Game.h"

DataLogger* DataLogger::ptrInstance = nullptr;
char DataLogger::DebugBuff[256] = {};

DataLogger::DataLogger()
{
	InitialXPos = Game::GetWidth() - 50.0f;
	InitialYPos = Game::GetHeight() - 50.0f;
	currentYPos = Game::GetHeight() - 50.0f;

	SpriteFontManager::Load("default", "Impact");

}

void DataLogger::privDelete()
{

	while (!stringQueue.empty()) // clear our sting queue 
	{
		delete stringQueue.front();
		stringQueue.pop();
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}

void DataLogger::privSetDLPos(float _xPos, float _yPos)
{
	InitialXPos = _xPos;
	InitialYPos = _yPos;
}

void DataLogger::privAdd(std::string s)
{
	// convert to sprite string 

	if (stringQueue.empty()) // handling string positions 
	{
		currentYPos = InitialYPos;
	}

	SpriteString* newSpriteString = new SpriteString(SpriteFontManager::Get("default"), s, InitialXPos, currentYPos);
	currentYPos -= newSpriteString->GetHeight();

	stringQueue.push(newSpriteString);
}

void DataLogger::privRender()
{
	while (!stringQueue.empty())
	{
		stringQueue.front()->Render();
		delete stringQueue.front();
		stringQueue.pop();
	}
}