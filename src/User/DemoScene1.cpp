// moving frigate demo scene recreated 

#include "DemoScene1.h"
#include "AzulCore.h"
#include "Frigate.h"
#include "Plane.h"
#include "Axis.h"


void DemoScene1::Initialize()
{

	// creating game obj
	 frig = new Frigate();
	 frig2 = new Frigate();
	 plane = new Plane();
	 axis = new Axis();

	 SetCollisionSelf<Frigate>();

}

void DemoScene1::SceneEnd()
{

	//delete game obj 
	delete axis;
	delete plane;
	delete frig;
	delete frig2;

}