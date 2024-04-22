// scene for testing game objects

#include "TestingScene.h"
//#include "Plane.h"
#include "GroundPlane.h"
#include "BulletFactory.h"
#include "Player.h"
#include "Tank.h"
#include "TankControllerAI.h"
#include "LevelManager.h"
#include "PatrolPatternWaypointLoop.h"


void TestingScene::Initialize()
{

	pBulletFactory = new BulletFactory();
	EnemyTank1 = new Tank(pBulletFactory, 10.0f, 600.0f);
	plane = new GroundPlane(0.0f, 0.0f);

	player = new Player(pBulletFactory, -30.0f, -100.0f);

	patrolPat = new PatrolPatternWaypointLoop();

	patrolPat->GeneratePattern(0.0f, 0.0f, 1000.0f, PatrolPatternWaypointLoop::PATTERNTYPE::LINE, 6);

	tankController = new TankControllerAI();
	tankController->setPatrolPattern(patrolPat);
	tankController->setTankToControl(EnemyTank1);

}

void TestingScene::SceneEnd()
{
	LevelManager::Terminate(); // the level manager is a singleton atm, deleting it here 

	delete pBulletFactory;
	delete player;
	delete plane;
	delete EnemyTank1;
	delete tankController;
	delete patrolPat; // this crashes sometimes when exiting quickly, deal with later 
}