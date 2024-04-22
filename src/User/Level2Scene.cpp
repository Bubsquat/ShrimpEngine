// scene for second level of the demo game 

#include "Level2Scene.h"
#include "GroundPlane.h"
#include "SkyBox.h"
#include "Bullet.h"
#include "Tank.h"
#include "BulletFactory.h"
#include "Player.h"
#include "LevelManager.h"
#include "TankControllerAI.h"
#include "PatrolPatternWaypointLoop.h"
#include "Hud.h"

Level2Scene::Level2Scene(int _score)
{
	LevelManager::UpdatePlayerScore(_score);
}

void Level2Scene::Initialize()
{

	// place level objects 

	PlaceGround(0.0f, 0.0f, 8);

	skyBox = new SkyBox();
	skyBox->setPos(0.0f, -4000.0f, 0.0f);

	// have to do this here
	hud = new Hud();
	LevelManager::SetHud(hud);

	// spawn in player

	pBulletFactory = new BulletFactory();
	player = new Player(pBulletFactory, 0.0, 0.0f);

	LevelManager::UpdatePlayerLocation(Vect(-100000.0f, 100000.0f, 100000.0f)); // dummy value before player updates

	// spawn enemies
	t1Controller = new TankControllerAI();
	EnemyTank1 = new Tank(pBulletFactory, 1700.0f, -1500.0f);
	t1PP = new PatrolPatternWaypointLoop();
	t1PP->GeneratePattern(1700.0f, -2000.0f, 100.0f, PatrolPatternWaypointLoop::PATTERNTYPE::LINE, 4);
	t1Controller->setPatrolPattern(t1PP);
	t1Controller->setTankToControl(EnemyTank1);
	LevelManager::AddEnemy();

	t2Controller = new TankControllerAI();
	EnemyTank2 = new Tank(pBulletFactory, -1500.0f, -1500.0f);
	t2PP = new PatrolPatternWaypointLoop();
	t2PP->GeneratePattern(-2000.0f, -1500.0f, 800.0f, PatrolPatternWaypointLoop::PATTERNTYPE::LINE, 5);
	t2Controller->setPatrolPattern(t2PP);
	t2Controller->setTankToControl(EnemyTank2);
	LevelManager::AddEnemy();

	t3Controller = new TankControllerAI();
	EnemyTank3 = new Tank(pBulletFactory, 1500.0f, 100.0f);
	t3PP = new PatrolPatternWaypointLoop();
	t3PP->GeneratePattern(2500.0f, 100.0f, 400.0f, PatrolPatternWaypointLoop::PATTERNTYPE::DIAMOND, -1);
	t3Controller->setPatrolPattern(t3PP);
	t3Controller->setTankToControl(EnemyTank3);
	LevelManager::AddEnemy();

	t4Controller = new TankControllerAI();
	EnemyTank4 = new Tank(pBulletFactory, 3000.0f, -150.0f);
	t4PP = new PatrolPatternWaypointLoop();
	t4PP->GeneratePattern(5000.0f, -150.0f, 500.0f, PatrolPatternWaypointLoop::PATTERNTYPE::ZIGZAG, 5);
	t4Controller->setPatrolPattern(t4PP);
	t4Controller->setTankToControl(EnemyTank4);
	LevelManager::AddEnemy();

	t5Controller = new TankControllerAI();
	EnemyTank5 = new Tank(pBulletFactory, -50.0f, 5000.0f);
	t5PP = new PatrolPatternWaypointLoop();
	t5PP->GeneratePattern(-50.0f, 6150.0f, 150.0f, PatrolPatternWaypointLoop::DIAMOND, -1);
	t5Controller->setPatrolPattern(t5PP);
	t5Controller->setTankToControl(EnemyTank5);
	LevelManager::AddEnemy();

	t6Controller = new TankControllerAI();
	EnemyTank6 = new Tank(pBulletFactory, 150.0f, 150.0f);
	t6PP = new PatrolPatternWaypointLoop();
	t6PP->GeneratePattern(150.0f, 150.0f, 1500.0f, PatrolPatternWaypointLoop::DIAMOND, -1);
	t6Controller->setPatrolPattern(t6PP);
	t6Controller->setTankToControl(EnemyTank6);
	LevelManager::AddEnemy();

	t7Controller = new TankControllerAI();
	EnemyTank7 = new Tank(pBulletFactory, 0.0f, -1000.0f);
	t7PP = new PatrolPatternWaypointLoop();
	t7PP->GeneratePattern(100.0f, -1000.0f, 150.0f, PatrolPatternWaypointLoop::LINE, 8);
	t7Controller->setPatrolPattern(t7PP);
	t7Controller->setTankToControl(EnemyTank7);
	LevelManager::AddEnemy();

	t8Controller = new TankControllerAI();
	EnemyTank8 = new Tank(pBulletFactory, -1000, 50.0f);
	t8PP = new PatrolPatternWaypointLoop();
	t8PP->GeneratePattern(-1000.0f, 50.0f, 2000.0f, PatrolPatternWaypointLoop::ZIGZAG, 12);
	t8Controller->setPatrolPattern(t8PP);
	t8Controller->setTankToControl(EnemyTank8);
	LevelManager::AddEnemy();

	// collision
	SetCollisionPair<Bullet, Tank>();


}



void Level2Scene::SceneEnd()
{

	LevelManager::Terminate(); // this should not be deleted if we are progressing to the next level probably 

	// remove enemies 
	delete t1Controller;
	delete EnemyTank1;
	delete t1PP;

	delete t2Controller;
	delete EnemyTank2;
	delete t2PP;

	delete t3Controller;
	delete EnemyTank3;
	delete t3PP;

	delete t4Controller;
	delete EnemyTank4;
	delete t4PP;

	delete t5Controller;
	delete EnemyTank5;
	delete t5PP;

	delete t6Controller;
	delete EnemyTank6;
	delete t6PP;

	delete t7Controller;
	delete EnemyTank7;
	delete t7PP;

	delete t8Controller;
	delete EnemyTank8;
	delete t8PP;

	// remove player
	delete player;
	delete pBulletFactory;
	delete hud;

	// remove terrain and skybox
	while (!gPlanes.empty())
	{
		delete gPlanes.front();
		gPlanes.pop();
	}

	delete skyBox;
}



void Level2Scene::PlaceGround(float X, float Z, int edgeLength)
{

	int numPlanes = edgeLength * edgeLength;

	// generate ground planes 

	GroundPlane* centerPlane = new GroundPlane(X, Z);
	gPlanes.push(centerPlane);

	int segLength = 1;
	int segsPassed = 0;

	int Xmul = 1;
	int Zmul = 0;

	int XGridPos = 0;
	int ZGridPos = 0;

	for (int i = 0; i < numPlanes - 1; i++)
	{
		XGridPos += Xmul;
		ZGridPos += Zmul;

		segsPassed++;

		//DebugMsg::out("X: %i Z: % i\n", XGridPos, ZGridPos);

		GroundPlane* newPlane = new GroundPlane(X + XGridPos * 2 * planeRadius, Z + ZGridPos * 2 * planeRadius);
		gPlanes.push(newPlane);

		if (segsPassed == segLength)
		{
			segsPassed = 0;

			int tmp = Xmul;
			Xmul = -Zmul;
			Zmul = tmp;

			if (Zmul == 0)
			{
				segLength++;
			}
		}
	}
}