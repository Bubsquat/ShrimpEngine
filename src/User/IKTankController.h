// base class for a IK tank controller

#ifndef _IKTankController
#define _IKTankController

#include "../GameObject.h"

class IKTank;

class IKTankController : public GameObject
{
public:

	IKTankController() = default;
	IKTankController(const IKTankController&) = delete;
	IKTankController& operator=(const IKTankController&) = delete;
	~IKTankController() = default;

	void SetTank(IKTank* tank);
	virtual void ReportHit() = 0;

protected:
	
	IKTank* pTank;

};

#endif _IKTankController
