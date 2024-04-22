// namespace IK system 

#include "InverseKinematics.h"
#include "Segment.h"
#include "Linkage.h"
#include <assert.h>

#include "DataLogger.h"
#include "Visualizer.h"

using namespace InverseKinematics;

void InverseKinematics::ApplyTransforms2Link(Linkage* L, const Vect& TargetPos)
{

	assert(L->GetNumSegments() == 2); // this apply transforms functions specific for 2 linkage ik 

	float distOff = (TargetPos - L->GetSegment(1)->GetEndPoint()).magSqr();

	if (distOff > ErrorMargin*ErrorMargin) // determine if the offset from the current endpoint and target point is worth recaulcuating the error
	{

		float link1Length = L->GetSegment(0)->GetLenght();
		float link2Length = L->GetSegment(1)->GetLenght();
		Vect toTarget = TargetPos - L->GetSegment(0)->GetStartPoint();
		Vect LinkOrigin = L->GetSegment(0)->GetStartPoint();

		// determine in target point is within reach of the arm 

		if (toTarget.magSqr() < ((link1Length + link2Length) * (link1Length + link2Length)))
		{
			// calculate ik solution (this is the slow version) 

			float theta = atan2f(TargetPos.X() - LinkOrigin.X(), TargetPos.Z() - LinkOrigin.Z()); // what to rotate Y around to make the manipulater's Z face the target point 

			float APrime = atanf((TargetPos.Y() - LinkOrigin.Y()) / abs(toTarget.mag()));

			float A = acosf((toTarget.magSqr() + (link1Length * link1Length) - (link2Length * link2Length)) / (2 * toTarget.mag() * link1Length)) + APrime;

			float B = MATH_PI - acosf(((link2Length * link2Length) + (link1Length * link1Length) - toTarget.magSqr()) / (2 * link2Length * link1Length));

			//DebugMsg::out("A: %f  B: %f  Theta: %f  \n", A, B, theta);
			
			L->SetSegmentRot(0, Matrix(ROT_X, MATH_PI / 2 -A) * Matrix(ROT_Y, theta));
			L->SetSegmentRot(1, Matrix(ROT_X, B + (MATH_PI / 2 - A)) * Matrix(ROT_Y, theta));
			
		}

	}

}
