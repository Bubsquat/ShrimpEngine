// scene for first level of the demo game 

#include "Level1Scene.h"
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

void Level1Scene::Initialize()
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

	// spawn enemies (if I were cool I would do the same thing I did with the player class here oh well)
	t1Controller = new TankControllerAI();
	EnemyTank1 = new Tank(pBulletFactory, 1700.0f, -2000.0f);
	t1PP = new PatrolPatternWaypointLoop();
	t1PP->GeneratePattern(1700.0f, -2000.0f, 100.0f, PatrolPatternWaypointLoop::PATTERNTYPE::LINE, 4);
	t1Controller->setPatrolPattern(t1PP);
	t1Controller->setTankToControl(EnemyTank1);
	LevelManager::AddEnemy();

	t2Controller = new TankControllerAI();
	EnemyTank2 = new Tank(pBulletFactory, -2000.0f, -3000.0f);
	t2PP = new PatrolPatternWaypointLoop();
	t2PP->GeneratePattern(-2000.0f, -3000.0f, 800.0f, PatrolPatternWaypointLoop::PATTERNTYPE::LINE, 5);
	t2Controller->setPatrolPattern(t2PP);
	t2Controller->setTankToControl(EnemyTank2);
	LevelManager::AddEnemy();

	t3Controller = new TankControllerAI();
	EnemyTank3 = new Tank(pBulletFactory, 2500.0f, 100.0f);
	t3PP = new PatrolPatternWaypointLoop();
	t3PP->GeneratePattern(2500.0f, 100.0f, 400.0f, PatrolPatternWaypointLoop::PATTERNTYPE::DIAMOND, -1);
	t3Controller->setPatrolPattern(t3PP);
	t3Controller->setTankToControl(EnemyTank3);
	LevelManager::AddEnemy();

	t4Controller = new TankControllerAI();
	EnemyTank4 = new Tank(pBulletFactory, 5000.0f, -150.0f);
	t4PP = new PatrolPatternWaypointLoop();
	t4PP->GeneratePattern(5000.0f, -150.0f, 500.0f, PatrolPatternWaypointLoop::PATTERNTYPE::ZIGZAG, 5);
	t4Controller->setPatrolPattern(t4PP);
	t4Controller->setTankToControl(EnemyTank4);
	LevelManager::AddEnemy();

	t5Controller = new TankControllerAI();
	EnemyTank5 = new Tank(pBulletFactory, -50.0f, 6000.0f);
	t5PP = new PatrolPatternWaypointLoop();
	t5PP->GeneratePattern(-50.0f, 6150.0f, 150.0f, PatrolPatternWaypointLoop::DIAMOND, -1);
	t5Controller->setPatrolPattern(t5PP);
	t5Controller->setTankToControl(EnemyTank5);
	LevelManager::AddEnemy();


	//float startPosX, float startPosZ, float pointDistance, PATTERNTYPE pat, int numPoints = -1

	// collision
	SetCollisionPair<Bullet, Tank>();


}

void Level1Scene::SceneEnd()
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

void Level1Scene::PlaceGround(float X, float Z, int edgeLength)
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