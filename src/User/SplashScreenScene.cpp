// scene for the background of the splash screen 

#include "SplashScreenScene.h"
#include "GroundPlane.h"
#include "SkyBox.h"
#include "LevelManager.h"
#include "IKTank.h"
#include "BulletFactory.h"
#include "IKTankControllerAI.h"
#include "PatrolPatternWaypointLoop.h"
#include "SplashScreen.h"

SplashScreenScene::SplashScreenScene(int _score)
{
	playerScore = _score;





}

void SplashScreenScene::Initialize()
{

	// create level objects
	//PlaceGround(0.0f, 0.0f, 8);
	SetTerrain("D2Level1Terrain");

	skyBox = new SkyBox();
	skyBox->setPos(0.0f, -2500.0f, 0.0f);
	
	LevelManager::UpdatePlayerLocation(dummyPlayerLoc); // our AI tank will never find this player



	// add an ai tank

	bf = new BulletFactory(); // tank needs a bullet factory (better than leaving a nullptr to cause a crash)
	tank = new IKTank(Vect(0, 100, 0));

	pp = new PatrolPatternWaypointLoop();
	pp->GeneratePattern(250.0f, 250.0f, 2000.0f, PatrolPatternWaypointLoop::PATTERNTYPE::DIAMOND);

	tankController = new IKTankControllerAI();
	tankController->setTankToControl(tank);
	tankController->setPatrolPattern(pp);

	// create splash screen

	if (playerScore != -1)
	{
		splashScreen = new SplashScreen(tank, playerScore);
	}
	else
	{
		splashScreen = new SplashScreen(tank);
	}
	

}

void SplashScreenScene::SceneEnd()
{

	LevelManager::Terminate();

	while (!gPlanes.empty())
	{
		delete gPlanes.front();
		gPlanes.pop();
	}

	delete splashScreen;
	delete skyBox;
	delete tankController;
	delete tank;
	delete bf;
	delete pp;

}



void SplashScreenScene::PlaceGround(float X, float Z, int edgeLength)
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