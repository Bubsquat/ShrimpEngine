// scene for demo game

#ifndef _DemoGameScene
#define _DemoGameScene

#include "AzulCore.h"
#include "../Scene.h"

class Axis;
class ShootingFrigate;
class Plane;
class Cottage;
class Tank;
class TestSprite;
class testTerrain;

class DemoGameScene : public Scene
{
public:

	DemoGameScene() = default;
	DemoGameScene(const DemoGameScene&) = delete;
	DemoGameScene& operator =(const DemoGameScene&) = delete;
	~DemoGameScene() = default;

	void Initialize();
	void SceneEnd();

private:

	Axis* axis;
	ShootingFrigate* frig;
	Plane* plane;
	Cottage* cottage;
	Cottage* cottage2;
	//Cottage* cottage3;
	Tank* tank;
	TestSprite* sprite;
	//testTerrain* pTerrain;

};

#endif _DemoGameScene