// scene for testing game objects

#ifndef _TestingScene
#define _TestingScene

#include "../Scene.h"

//class Plane;
class GroundPlane;
class BulletFactory;
class Player;
class Tank;
class TankControllerAI;
class PatrolPatternWaypointLoop;

class TestingScene : public Scene
{
public:

	TestingScene() = default;
	TestingScene(const TestingScene&) = delete;
	TestingScene& operator= (const TestingScene&) = delete;
	~TestingScene() = default;

	void Initialize();
	void SceneEnd();

private:

	Tank* EnemyTank1;
	//Plane* plane;
	GroundPlane* plane;
	TankControllerAI* tankController;
	BulletFactory* pBulletFactory;
	Player* player;
	PatrolPatternWaypointLoop* patrolPat;

};



#endif _TestingScene

