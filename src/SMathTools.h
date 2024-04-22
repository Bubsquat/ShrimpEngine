// namespace math library 

#ifndef _SMathTools
#define _SMathTools

#include "AzulCore.h"

class CollisionVolumeAABB;
class CollisionVolumeBSphere;
class CollisionVolumeOBB;
class CollisionVolume;

namespace SMathTools
{

	bool IntervalIntersection(const float intervalAMin, const float intervalAMax, const float intervalBMin, const float intervalBMax);
	float Clamp(const float value, const float rangeMin, const float rangeMax);
	int Clamp(const int value, const int rangeMin, const int rangeMax);
	bool ValueWithinInterval(const float value, const float rangeMin, const float rangeMax);
	Vect ProjVect(const Vect& A, const Vect& alongB);
	Vect VectAbs(const Vect& A);

	Vect MinVect(const Vect& A, const Vect& B);
	Vect MaxVect(const Vect& A, const Vect& B);

	bool IntersectBSphere(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
	bool PointIntersectBSphere(const Vect& point, const CollisionVolumeBSphere& B);
	bool PointIntersectOBB(const Vect& point, const CollisionVolumeOBB& B);
	bool Intersect(const CollisionVolume& A, const CollisionVolume& B);
	bool IntersectAABB(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B);
	bool IntersectBSphereAABB(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B);
	bool IntersectOBB(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	bool AxisTest(const Vect& axis, const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	bool AxisTest(const Vect& axis, const CollisionVolumeOBB& A, const CollisionVolumeAABB& B);

	bool IntersectBSphereOBB(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B);
	bool IntersectAABBOBB(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B);

}




#endif _SMathTools

