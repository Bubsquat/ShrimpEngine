//scene for the first level of the second version of the demo game

#ifndef _Demo2Level1Scene
#define _Demo2Level1Scene

#include "../Scene.h"

class IKTank;
class SkyBox;
class IKTankControllerPlayer;
class IKTankControllerAI;
class BulletFactory; 
class Bullet;
class Hud;
class PatrolPatternWaypointLoop;

class Demo2Level1Scene : public Scene
{
public:

	Demo2Level1Scene() = default;
	Demo2Level1Scene(const Demo2Level1Scene&) = delete;
	Demo2Level1Scene& operator=(const Demo2Level1Scene&) = delete;
	~Demo2Level1Scene() = default;

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

};

#endif _Demo2Level1Scene

