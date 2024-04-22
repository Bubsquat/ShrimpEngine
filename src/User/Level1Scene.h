// scene for first level of the demo game 

#ifndef _Level1Scene
#define _Level1Scene

#include "../Scene.h"
#include <queue>

class GroundPlane;
class BulletFactory;
class Player;
class Tank;
class TankControllerAI;
class PatrolPatternWaypointLoop;
class SkyBox;
class Hud;

class Level1Scene : public Scene
{
public:

	Level1Scene() = default;
	Level1Scene(const Level1Scene&) = delete;
	Level1Scene& operator= (const Level1Scene&) = delete;
	~Level1Scene() = default;

	void Initialize();
	void SceneEnd();

private:


	void PlaceGround(float X, float Z, int edgeLength);

	// ground planes
	using GroundPlanes = std::queue<GroundPlane*>;
	GroundPlanes gPlanes;
	const int numRings = 3;
	const float planeRadius = 750.0f;

	SkyBox* skyBox;

	GroundPlane* plane;
	BulletFactory* pBulletFactory;
	Player* player;

	Hud* hud;

	// level specific enemy placement

	Tank* EnemyTank1;
	Tank* EnemyTank2;
	Tank* EnemyTank3;
	Tank* EnemyTank4;
	Tank* EnemyTank5;

	TankControllerAI* t1Controller;
	TankControllerAI* t2Controller;
	TankControllerAI* t3Controller;
	TankControllerAI* t4Controller;
	TankControllerAI* t5Controller;

	PatrolPatternWaypointLoop* t1PP;
	PatrolPatternWaypointLoop* t2PP;
	PatrolPatternWaypointLoop* t3PP;
	PatrolPatternWaypointLoop* t4PP;
	PatrolPatternWaypointLoop* t5PP;
};



#endif _Level1Scene

