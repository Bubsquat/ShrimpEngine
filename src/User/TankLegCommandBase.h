// base class for commands for moving tank legs (necessary bc the leg class is not specific to the left or right side of the tank)

#ifndef _TankLegCommandBase
#define _TankLegCommandBase

#include "AzulCore.h"

class TankLegCommandBase
{
public:

	enum LegPart
	{
		Thigh,
		Foot
	};

	TankLegCommandBase() = default;
	TankLegCommandBase(const TankLegCommandBase&) = delete;
	TankLegCommandBase& operator= (const TankLegCommandBase&) = delete;
	~TankLegCommandBase() = default;

	//virtual void ApplyOffsets(Matrix ToOffset) = 0;
	virtual Vect GetOffset(LegPart p, int num) = 0;
	virtual Vect GetRot(LegPart p, int num) = 0;

private:

};



#endif _TankLegCommandBase
