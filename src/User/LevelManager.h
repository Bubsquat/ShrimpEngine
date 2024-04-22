// singleton for keeping track of level statistics like player location and number of enemies 

#ifndef _LevelManager
#define _LevelManager

#include "AzulCore.h"
class Scene;
class Hud;

class LevelManager
{
private:

	static LevelManager* ptrInstance;

	LevelManager();
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	~LevelManager() = default;

	static LevelManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new LevelManager();
		}
		return *ptrInstance;
	}

	Vect playerLocation;
	Scene* currentScene;

	int enemyNumber; 
	int currentPlayerScore;
	int currentPlayerHealth;

	Hud* hud;

	const float shortKill = 1500.0f;
	const float longShot = 10000.0f; 

	void privDelete();
	void privAddEnemy();
	void privRemoveEnemy();
	void privUpdatePlayerScore(float dist);
	void privUpdatePlayerScore(int score);
	int privGetEnemyNumber();
	void privUpdatePlayerHealth(int health);
	void privSetHud(Hud* hud);
	

public:

	static const Vect GetPlayerLocation() { return Instance().playerLocation; };
	static void UpdatePlayerLocation(Vect loc) { Instance().playerLocation = loc; };
	static void Terminate() { Instance().privDelete(); };
	static void RemoveEnemy() { Instance().privRemoveEnemy(); }
	static void AddEnemy() { Instance().privAddEnemy(); };
	static void UpdatePlayerScore(float dist) { Instance().privUpdatePlayerScore(dist); };
	static void UpdatePlayerScore(int score) { Instance().privUpdatePlayerScore(score); };
	static int GetEnemyNumber() { return Instance().privGetEnemyNumber(); };
	static void UpdatePlayerHealth(int health) { Instance().privUpdatePlayerHealth(health); };
	static void SetHud(Hud* hud) { Instance().privSetHud(hud); };

};




#endif _LevelManager
