// scene for demo game

#include "DemoGameScene.h"
#include "AzulCore.h"
#include "ShootingFrigate.h"
#include "Plane.h"
#include "Axis.h"
#include "Cottage.h"
#include "Bullet.h"
#include "Tank.h"
#include "TestSprite.h"
#include "../TerrainManager.h"


void DemoGameScene::Initialize()
{
	// creating game obj
	frig = new ShootingFrigate();
	axis = new Axis();

	cottage = new Cottage();
	cottage2 = new Cottage();

	cottage->SetPosition(Vect(100, 0, 100));
	cottage->SetPosition(Vect(-100, 0, -100));

	SetCollisionPair<ShootingFrigate, Cottage>();



	SetTerrain("testTerrain");

	SetCollisionTerrain<ShootingFrigate>();

}

void DemoGameScene::SceneEnd()
{
	//delete game obj 
	delete axis;
	delete frig;
	delete cottage;
	delete cottage2;
}