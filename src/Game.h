#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"
#include <queue>

class Scene;
class VisualizerDrawCmdBase;

class Game: public Engine
{
	
private:	
	// legacy
	Game( const char* windowName, const int Width,const int Height);

	Game() = default;
	Game(const Game&) = delete;
	Game& operator =(const Game&) = delete;
	//~Game() = default;


	static Game* ptrInstance;

	static Game& Instance()
	{

		if (!ptrInstance)
		{
			ptrInstance = new Game();
		}
		return *ptrInstance;
	}

	// Azul Methods
	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	// user defined methods
	void LoadResources();
	void GameInitialize();
	void GameEnd();


	//cleanup 
	void priveTermintate();

	friend class GameAttorney;

public:

	static void StartGame() 
	{ 
		Instance().run();
		Instance().priveTermintate();
	}
	static void Terminate() { Instance().priveTermintate(); }

	// services 
	static void SetWindowName(const char* windowName);
	static void SetWindowHeight(int x, int y);
	static void setClearColor(float r, float g, float b, float a);

	static int GetWidth();
	static int GetHeight();

};

#endif