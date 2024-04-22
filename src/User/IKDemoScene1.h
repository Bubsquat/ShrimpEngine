// first demo scene for testing ik systems

#ifndef _IKDemoScene1
#define _IKDemoScene1

#include "AzulCore.h"
#include "../Scene.h"

class Axis;
class Plane;
class IKTestingObj;
class TestMover;

class IKDemoScene1 : public Scene
{
public:

	IKDemoScene1() = default;
	IKDemoScene1(const IKDemoScene1&) = delete;
	IKDemoScene1& operator =(const IKDemoScene1&) = delete;
	~IKDemoScene1() = default;

	void Initialize();
	void SceneEnd();

private:

	//bg elements
	Axis* axis;
	Plane* plane;

	//contents 
	IKTestingObj* testObj;
	TestMover* mover;

};

#endif _IKDemoScene1