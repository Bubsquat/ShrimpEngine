// namespace IK system 

#ifndef _InverseKinematics
#define _InverseKinematics

#include "AzulCore.h"

class Linkage;

namespace InverseKinematics
{
	const float ErrorMargin = 0.0f;

	void ApplyTransforms2Link(Linkage* L, const Vect& TargetPos);

}


#endif _InverseKinematics
