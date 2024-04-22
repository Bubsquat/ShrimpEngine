// base class for a IK tank controller

#include "IKTankController.h"
#include "IKTank.h"

void IKTankController::SetTank(IKTank* tank)
{
	this->pTank = tank;
	pTank->SetController(this);
}