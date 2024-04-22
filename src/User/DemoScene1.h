// moving frigate demo scene recreated 

#ifndef _DemoScene1
#define _DemoScene1

#include "AzulCore.h"
#include "../Scene.h"

class Axis;
class Frigate;
class Plane;

class DemoScene1 : public Scene
{
public:
	
	DemoScene1() = default;
	DemoScene1(const DemoScene1 &) = delete;
	DemoScene1& operator =(const DemoScene1&) = delete;
	~DemoScene1() = default;

	void Initialize();
	void SceneEnd();

private:

	Axis* axis;
	Frigate* frig;
	Frigate* frig2;
	Plane* plane;

};

#endif _DemoScene1
