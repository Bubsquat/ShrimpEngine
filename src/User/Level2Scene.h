// scene for second level of the demo game 

#ifndef _Level2Scene
#define _Level2Scene

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

class Level2Scene : public Scene
{
public:

	Level2Scene() = delete;
	Level2Scene(int score);
	Level2Scene(const Level2Scene&) = delete;
	Level2Scene& operator= (const Level2Scene&) = delete;
	~Level2Scene() = default;

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
	Tank* EnemyTank6;
	Tank* EnemyTank7;
	Tank* EnemyTank8;

	TankControllerAI* t1Controller;
	TankControllerAI* t2Controller;
	TankControllerAI* t3Controller;
	TankControllerAI* t4Controller;
	TankControllerAI* t5Controller;
	TankControllerAI* t6Controller;
	TankControllerAI* t7Controller;
	TankControllerAI* t8Controller;

	PatrolPatternWaypointLoop* t1PP;
	PatrolPatternWaypointLoop* t2PP;
	PatrolPatternWaypointLoop* t3PP;
	PatrolPatternWaypointLoop* t4PP;
	PatrolPatternWaypointLoop* t5PP;
	PatrolPatternWaypointLoop* t6PP;
	PatrolPatternWaypointLoop* t7PP;
	PatrolPatternWaypointLoop* t8PP;

};



#endif _Level1Scene