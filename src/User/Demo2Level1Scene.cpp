//scene for the first level of the second version of the demo game

#include "Demo2Level1Scene.h"

#include "IKTank.h"
#include "Bullet.h"
#include "SkyBox.h"
#include "IKTankControllerPlayer.h"
#include "IKTankControllerAI.h"
#include "BulletFactory.h"
#include "Hud.h"
#include "LevelManager.h"
#include "PatrolPatternWaypointLoop.h"

void Demo2Level1Scene::Initialize()
{

	// level scenery
	SetTerrain("D2Level1Terrain");

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

	//		set up tanks 
	//player
	playerTank = new IKTank(Vect(0, 50, -40));
	playerTank->SetBulletFactory(bulletFactory);
	playerController = new IKTankControllerPlayer();
	playerController->SetTank(playerTank);
	playerTank->SetController(playerController);

	//Enemies 
	// E1
	AITank1 = new IKTank(Vect(300.0f, 50.0f, 5800.0f));
	AITank1->SetBulletFactory(bulletFactory);

	P1 = new PatrolPatternWaypointLoop();
	P1->GeneratePattern(3300.0f, 5800.0f, 5500.0f, PatrolPatternWaypointLoop::ZIGZAG, 3);

	AI1 = new IKTankControllerAI();
	AI1->setTankToControl(AITank1);
	AI1->setPatrolPattern(P1);
	AITank1->SetController(AI1);
	LevelManager::AddEnemy();

	//E2 
	AITank2 = new IKTank(Vect(-100, 50, -6000));
	AITank2->SetBulletFactory(bulletFactory);
	AI2 = new IKTankControllerAI();
	P2 = new PatrolPatternWaypointLoop();
	P2->GeneratePattern(-100.0f, -3000.0f, 6000.0f, PatrolPatternWaypointLoop::DIAMOND);
	AI2->setTankToControl(AITank2);
	AI2->setPatrolPattern(P2);
	AITank2->SetController(AI2);
	LevelManager::AddEnemy();

	//E3
	AITank3 = new IKTank(Vect(-21000, 100, 200));
	AITank3->SetBulletFactory(bulletFactory);
	AI3 = new IKTankControllerAI();
	P3 = new PatrolPatternWaypointLoop();
	P3->GeneratePattern(-21000, 200, 5000, PatrolPatternWaypointLoop::LINE, 4);
	AI3->setTankToControl(AITank3);
	AI3->setPatrolPattern(P3);
	AITank3->SetController(AI3);
	LevelManager::AddEnemy();
	


}

void Demo2Level1Scene::SceneEnd()
{
	delete playerTank;
	delete skyBox;
	delete playerController;
	delete bulletFactory;
	delete hud;

	LevelManager::Terminate();

	delete AI1;
	delete AITank1;
	delete P1;
	delete AI2;
	delete AITank2;
	delete P2;
	delete AI3;
	delete AITank3;
	delete P3;

}

