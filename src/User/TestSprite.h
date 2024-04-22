// class for testing sprite functionality 

#ifndef _TestSprite
#define _TestSprite

#include "AzulCore.h"
#include "../GameObject.h"

class SESprite;
class SpriteString;

class TestSprite : public GameObject
{
public:

	TestSprite();
	TestSprite(const TestSprite&) = delete;
	TestSprite& operator =(const TestSprite&) = delete;
	~TestSprite();

	void Update();
	void Draw();
	void Draw2D();
	void SceneEntry();
	void SceneExit();

	void Alarm0();

private:

	float offsetVar;

	SESprite* sprite1;
	SESprite* sprite2;

	SESprite* letterTest;
	int testLetter;
	SpriteString* spriteString;

	Vect s1Pos;
	Vect s2Pos;

	float s1SpeedX = 5.0f;
	float s1SpeedY = 5.0f;
	float s2Speed = 0.07f;

	Rect* stitchRect;
};

#endif _TestSprite

