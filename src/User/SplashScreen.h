// game object that contains the camera, sprites, and keydetection for the splash screen 

#ifndef _SplashScreen
#define _SplashScreen

#include "AzulCore.h"
#include "../GameObject.h"

class IKTank;
class SESprite;
class SpriteString;

class SplashScreen : public GameObject
{
public:

	SplashScreen() = delete;
	SplashScreen(IKTank* tank, int score = -1); // needs a tank so its camera can follow the demo tank 
	SplashScreen(const SplashScreen&) = delete;
	SplashScreen& operator =(const SplashScreen&) = delete;
	~SplashScreen();

	void Update();
	void Draw();
	void Draw2D();
	void SceneEntry();
	void SceneExit();

	void KeyPressed(AZUL_KEY k);

private:

	SESprite* splashScreenGraphics;
	IKTank* pTank;

	Camera* SSCamera;
	Matrix camPos;
	Matrix camRot;
	Matrix camOffset;
	Vect lookAt;
	const float camRotSpeed = 0.0100f;

	const float textHeight = 150.0f;
	const float textOrigin = 1200;
	const float textSpeed = 2.8f; 

	float s1pos;
	float s2pos;
	float s3pos;

	SpriteString* string1;
	SpriteString* string2;
	SpriteString* string3;

	SpriteString* scoreString;
	int score;

};

#endif _SplashScreen
