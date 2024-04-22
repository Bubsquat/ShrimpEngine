//scene for the second level of the second version of the demo game

#include "Demo2Level2Scene.h"

#include "IKTank.h"
#include "Bullet.h"
#include "SkyBox.h"
#include "IKTankControllerPlayer.h"
#include "IKTankControllerAI.h"
#include "BulletFactory.h"
#include "Hud.h"
#include "LevelManager.h"
#include "PatrolPatternWaypointLoop.h"

Demo2Level2Scene::Demo2Level2Scene(int _playerScore)
{
	LevelManager::UpdatePlayerScore(_playerScore);
}

void Demo2Level2Scene::Initialize()
{
	// level scenery
	SetTerrain("D2Level2Terrain");

	skyBox = new SkyBox();
	skyBox->setPos(0.0f, -10000.0f, 0.0f);

	// collision 
	SetCollisionPair<IKTank, Bullet>();
	//SetCollisionTerrain<Bullet>();

	// other game objects 
	hud = new Hud();
	LevelManager::SetHud(hud);

	LevelManager::UpdatePlayerLocation(Vect(-100000.0f, 100000.0f, 100000.0f)); // dummy value before player updates

	bulletFactory = new BulletFactory();

	// set up tanks 
	//player
	playerTank = new IKTank(Vect(0, 50, 0));
	playerTank->SetBulletFactory(bulletFactory);
	playerController = new IKTankControllerPlayer();
	playerController->SetTank(playerTank);
	playerTank->SetController(playerController);

	//Enemies 
	// E1
	AITank1 = new IKTank(Vect(300.0f, 50.0f, 3000.0f));
	AITank1->SetBulletFactory(bulletFactory);

	P1 = new PatrolPatternWaypointLoop();
	P1->GeneratePattern(2300.0f, 3000.0f, 5500.0f, PatrolPatternWaypointLoop::ZIGZAG, 3);

	AI1 = new IKTankControllerAI();
	AI1->setTankToControl(AITank1);
	AI1->setPatrolPattern(P1);
	AITank1->SetController(AI1);
	LevelManager::AddEnemy();

	//E2 
	AITank2 = new IKTank(Vect(-100, 50, 5000));
	AITank2->SetBulletFactory(bulletFactory);
	AI2 = new IKTankControllerAI();
	P2 = new PatrolPatternWaypointLoop();
	P2->GeneratePattern(-100.0f, 5000.0f, 6000.0f, PatrolPatternWaypointLoop::DIAMOND);
	AI2->setTankToControl(AITank2);
	AI2->setPatrolPattern(P2);
	AITank2->SetController(AI2);
	LevelManager::AddEnemy();

	//E3
	AITank3 = new IKTank(Vect(2100, 100, 200));
	AITank3->SetBulletFactory(bulletFactory);
	AI3 = new IKTankControllerAI();
	P3 = new PatrolPatternWaypointLoop();
	P3->GeneratePattern(2100, 200, 5000, PatrolPatternWaypointLoop::LINE, 4);
	AI3->setTankToControl(AITank3);
	AI3->setPatrolPattern(P3);
	AITank3->SetController(AI3);
	LevelManager::AddEnemy();

	//E4 
	AITank4 = new IKTank(Vect(100, 50, -1000));
	AITank4->SetBulletFactory(bulletFactory);
	AI4 = new IKTankControllerAI();
	P4 = new PatrolPatternWaypointLoop();
	P4->GeneratePattern(0, -1000, 3000.0f, PatrolPatternWaypointLoop::DIAMOND);
	AI4->setTankToControl(AITank4);
	AI4->setPatrolPattern(P4);
	AITank4->SetController(AI4);
	LevelManager::AddEnemy();
	
}

void Demo2Level2Scene::SceneEnd()
{

	LevelManager::Terminate();

	delete bulletFactory;
	delete skyBox;
	delete hud;

	delete playerTank;
	delete playerController;
	
	delete AI1;
	delete AITank1;
	delete P1;
	delete AI2;
	delete AITank2;
	delete P2;
	delete AI3;
	delete AITank3;
	delete P3;
	delete AI4;
	delete AITank4;
	delete P4;
}