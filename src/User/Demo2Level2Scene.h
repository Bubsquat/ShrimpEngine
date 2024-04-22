//scene for the second level of the second version of the demo game

#ifndef _Demo2Level2Scene
#define _Demo2Level2Scene

#include "../Scene.h"

class IKTank;
class SkyBox;
class IKTankControllerPlayer;
class IKTankControllerAI;
class BulletFactory;
class Bullet;
class Hud;
class PatrolPatternWaypointLoop;

class Demo2Level2Scene : public Scene
{
public:

	Demo2Level2Scene(int playerScore);
	Demo2Level2Scene(const Demo2Level2Scene&) = delete;
	Demo2Level2Scene& operator=(const Demo2Level2Scene&) = delete;
	~Demo2Level2Scene() = default;

	void Initialize();
	void SceneEnd();


private:

	IKTank* playerTank;
	SkyBox* skyBox;
	IKTankControllerPlayer* playerController;
	BulletFactory* bulletFactory;
	Hud* hud;

	PatrolPatternWaypointLoop* P1;
	IKTankControllerAI* AI1;
	IKTank* AITank1;
	PatrolPatternWaypointLoop* P2;
	IKTankControllerAI* AI2;
	IKTank* AITank2;
	PatrolPatternWaypointLoop* P3;
	IKTankControllerAI* AI3;
	IKTank* AITank3;
	PatrolPatternWaypointLoop* P4;
	IKTankControllerAI* AI4;
	IKTank* AITank4;
	PatrolPatternWaypointLoop* P5;
	IKTankControllerAI* AI5;
	IKTank* AITank5;

};

#endif _Demo2Level2Scene