// singleton for keeping track of level statistics like player location and number of enemies 

#include "LevelManager.h"
#include "Hud.h"
#include "SplashScreenScene.h"
#include "../SceneManager.h"
#include "Demo2Level2Scene.h"
#include "Demo2Level1Scene.h"

LevelManager* LevelManager::ptrInstance = nullptr;

LevelManager::LevelManager()
{
	enemyNumber = 0;
	currentPlayerScore = 0;
}

void LevelManager::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void LevelManager::privRemoveEnemy()
{
	enemyNumber--;

	if (enemyNumber == 0) // level end condition updated here 
	{
		SceneManager::SubmitSceneChange(new Demo2Level2Scene(currentPlayerScore));
	}

}

void LevelManager::privAddEnemy()
{
		enemyNumber++;
}

void LevelManager::privUpdatePlayerScore(float dist)
{

	if (dist <= shortKill)
	{

		// report short kill to hud 
		currentPlayerScore += 800;
		hud->ReportKill(Hud::KillType::POINTBLANK);

	}
	else if (dist >= longShot)
	{
		// report longshot to hud
		currentPlayerScore += 800;
		hud->ReportKill(Hud::KillType::LONGSHOT);

	}
	else
	{
		//report kill to hud
		currentPlayerScore += 500;
		hud->ReportKill(Hud::KillType::KILL);
	}

}

void LevelManager::privUpdatePlayerScore(int _score)
{
	currentPlayerScore = _score;
}

int LevelManager::privGetEnemyNumber()
{
	return enemyNumber;
}

void LevelManager::privUpdatePlayerHealth(int health)
{
	currentPlayerHealth = health;
	hud->SetPlayerHealth(health);

	if (currentPlayerHealth == 0)
	{
		// end level condition 

		SceneManager::SubmitSceneChange(new SplashScreenScene(currentPlayerScore));

	}

}

void LevelManager::privSetHud(Hud* _hud)
{
	hud = _hud;
}

