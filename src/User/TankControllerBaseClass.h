// base class for tank controller 

#ifndef _TankControllerBaseClass
#define _tankControllerBaseClass

#include "../GameObject.h"

class Tank;

class TankControllerBaseClass : public GameObject
{
public:

	TankControllerBaseClass() = default;
	TankControllerBaseClass(const TankControllerBaseClass&) = delete;
	TankControllerBaseClass& operator= (const TankControllerBaseClass&) = delete;
	virtual ~TankControllerBaseClass() {};

	virtual void setTankToControl(Tank* _Tank) = 0;
	virtual void ReportHit() = 0;

	//void Update();
	//void Draw();
	//void SceneEntry();
	//void SceneExit();

private:

};


#endif _TankControllerBaseClass




