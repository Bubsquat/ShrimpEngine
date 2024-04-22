// first demo scene for testing ik systems

#include "IKDemoScene1.h"

#include "Axis.h"
#include "Plane.h"
#include "IKTestingObj.h"
#include "TestMover.h"

void IKDemoScene1::Initialize()
{

	//bg elements
	axis = new Axis();
	plane = new Plane();

	//contents 
	testObj = new IKTestingObj();
	mover = new TestMover();
	mover->SetPosition(Vect(15.0f, 60.0f, 130.0f));
	testObj->setTestMover(mover);

}

void IKDemoScene1::SceneEnd()
{
	//bg elements
	delete axis;
	delete plane;

	//contents
	delete testObj;
	delete mover;
}