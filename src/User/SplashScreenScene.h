// scene for the background of the splash screen 

#ifndef _SplashScreenScene
#define _SplashScreenScene

#include "../Scene.h"
#include <queue>

class SkyBox;
class GroundPlane;
class BulletFactory;
class PatrolPatternWaypointLoop;
class SplashScreen;
class IKTank;
class IKTankControllerAI;

class SplashScreenScene : public Scene
{
public:

	SplashScreenScene(int score);
	SplashScreenScene(const SplashScreenScene&) = delete;
	SplashScreenScene& operator =(const SplashScreenScene&) = delete;
	~SplashScreenScene() = default;

	void Initialize();
	void SceneEnd();

private:

	void PlaceGround(float X, float Z, int edgeLength);

	using GroundPlanes = std::queue<GroundPlane*>;
	GroundPlanes gPlanes;
	const int numRings = 3;
	const float planeRadius = 750.0f;

	const Vect dummyPlayerLoc{ 50000000.0f, 50000000.0f, 50000000.0f };

	SkyBox* skyBox;

	IKTank* tank;
	IKTankControllerAI* tankController;
	BulletFactory* bf;

	PatrolPatternWaypointLoop* pp;

	SplashScreen* splashScreen;

	int playerScore;
};

#endif _SplashScreenScene
