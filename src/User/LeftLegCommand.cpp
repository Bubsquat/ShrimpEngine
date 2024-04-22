// command for the left leg of the tank 

#include "LeftLegCommand.h"
#include <assert.h>

Vect LeftLegCommand::GetOffset(LegPart p, int num)
{

	switch (p)
	{
	case LegPart::Thigh:
		return ThighPos[num];
		break;
	case LegPart::Foot:
		return FootPos[num];
		break;
	}

	assert("Error on LegCmd Switch");
	return Vect(0.0f, 0.0f, 0.0f);
}

Vect LeftLegCommand::GetRot(LegPart p, int num)
{

	switch (p)
	{
	case LegPart::Thigh:
		return ThighRot[num];
		break;
	case LegPart::Foot:
		return FootRot[num];
		break;
	}

	assert("Error on LegCmd Switch");
	return Vect(0.0f, 0.0f, 0.0f);
}