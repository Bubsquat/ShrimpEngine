// game object for testing ik system features

#ifndef _IKTestingObj
#define _IKTestingObj

#include "../GameObject.h"
#include "AzulCore.h"

class Segment;
class Linkage;
class TestMover;

class IKTestingObj : public GameObject
{
public:

	IKTestingObj();
	IKTestingObj(const IKTestingObj&) = delete;
	IKTestingObj& operator=(const IKTestingObj&) = delete;
	~IKTestingObj();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void Alarm0();
	void Alarm1();

	void setTestMover(TestMover* mover);

private:

	GraphicsObject_WireframeConstantColor* pGoTestBox;
	GraphicsObject_ColorNoTexture* pGoTestBox2;
	Linkage* linkage1;
	Matrix boxScale;
	Matrix boxWorld;
	Matrix box2World;
	Vect targetPoint;
	TestMover* mover;

};


#endif _IKTestingObj

