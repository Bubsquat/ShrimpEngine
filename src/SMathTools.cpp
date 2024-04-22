// namespace math library 

#include "SMathTools.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolume.h"

#include "DataLogger.h"

using namespace SMathTools;

bool SMathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
	return A.IntersectAccept(B);
}

bool SMathTools::IntersectBSphere(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	// calculate distance between BShpere centeres 

	float distanceSquared; // distance squared 
	Vect ACenter = A.GetCenter();
	Vect BCenter = B.GetCenter();

	distanceSquared = (ACenter.X() - BCenter.X()) * (ACenter.X() - BCenter.X());
	distanceSquared += (ACenter.Y() - BCenter.Y()) * (ACenter.Y() - BCenter.Y());
	distanceSquared += (ACenter.Z() - BCenter.Z()) * (ACenter.Z() - BCenter.Z());

	// get the sum of the radi squared 
	float radiusSquared = 0.0f;

	radiusSquared = (A.GetRadius() + B.GetRadius()) * (A.GetRadius() + B.GetRadius());

	return radiusSquared > distanceSquared;
}

bool SMathTools::IntersectAABB(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{

	return (IntervalIntersection(A.GetMin().X(), A.GetMax().X(), B.GetMin().X(), B.GetMax().X()) &&
		IntervalIntersection(A.GetMin().Y(), A.GetMax().Y(), B.GetMin().Y(), B.GetMax().Y()) &&
		IntervalIntersection(A.GetMin().Z(), A.GetMax().Z(), B.GetMin().Z(), B.GetMax().Z())
		);
}

bool SMathTools::PointIntersectBSphere(const Vect& point, const CollisionVolumeBSphere& B)
{
	float distanceSquared = 0.0f;
	Vect BCenter = B.GetCenter();

	distanceSquared = (point.X() - BCenter.X()) * (point.X() - BCenter.X());
	distanceSquared += (point.Y() - BCenter.Y()) * (point.Y() - BCenter.Y());
	distanceSquared += (point.Z() - BCenter.Z()) * (point.Z() - BCenter.Z());

	float radiusSquared = B.GetRadius() * B.GetRadius();

	return radiusSquared > distanceSquared;
}

bool SMathTools::IntersectBSphereAABB(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B)
{

	Vect clampedPoint;
	clampedPoint.X() = Clamp(A.GetCenter().X(), B.GetMin().X(), B.GetMax().X());
	clampedPoint.Y() = Clamp(A.GetCenter().Y(), B.GetMin().Y(), B.GetMax().Y());
	clampedPoint.Z() = Clamp(A.GetCenter().Z(), B.GetMin().Z(), B.GetMax().Z());

	return PointIntersectBSphere(clampedPoint, A);

}

bool SMathTools::IntersectOBB(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{

	// compute axis to project 
	// 3 face normals for A 
	// 3 face normals for B
	// 3x3 cross products of above

	// A face normals
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_0), A, B)) return false;
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_1), A, B)) return false;
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_2), A, B)) return false;
	// B face normals
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_0), A, B)) return false;
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_1), A, B)) return false;
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_2), A, B)) return false;

	// cross products
	// 
	// A0 x B0
	Vect Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A0 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A0 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B0
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B0
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}

	return true;
}

bool SMathTools::AxisTest(const Vect& _axis, const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{

	// proj of A onto axis
	Vect axis = _axis;
	axis.W() = 0;
	
	// max projection of a onto v 

	Vect locAxisA = axis * A.GetWorld().getInv();

	float maxProjA = (abs(locAxisA.X() * A.GetLocalHalfDiagonal().X()) + abs(locAxisA.Y() * A.GetLocalHalfDiagonal().Y()) + abs(locAxisA.Z() * A.GetLocalHalfDiagonal().Z())) / axis.mag();
	maxProjA *= A.GetWorld().get(MatrixRowType::ROW_0).magSqr(); // assuming uniform scaling? 

	// max projection of b onto v

	Vect locAxisB = axis * B.GetWorld().getInv();

	float maxProjB = (abs(locAxisB.X() * B.GetLocalHalfDiagonal().X()) + abs(locAxisB.Y() * B.GetLocalHalfDiagonal().Y()) + abs(locAxisB.Z() * B.GetLocalHalfDiagonal().Z())) / axis.mag();
	maxProjB *= B.GetWorld().get(MatrixRowType::ROW_0).magSqr();

	// calculate D

	float D = abs((B.GetCenter() - A.GetCenter()).dot(axis)) / axis.mag();

	//DataLogger::Add("ProjA:  %f  ProjB:  %f  D:  %f", maxProjA, maxProjB, D);

	return D <= maxProjA + maxProjB;

}

bool SMathTools::AxisTest(const Vect& _axis, const CollisionVolumeOBB& A, const CollisionVolumeAABB& B)
{
	// proj of A onto axis

		// proj of A onto axis
	Vect axis = _axis;
	axis.W() = 0;

	// max projection of a onto v 

	Vect locAxisA = axis * A.GetWorld().getInv();

	float maxProjA = (abs(locAxisA.X() * A.GetLocalHalfDiagonal().X()) + abs(locAxisA.Y() * A.GetLocalHalfDiagonal().Y()) + abs(locAxisA.Z() * A.GetLocalHalfDiagonal().Z())) / axis.mag();
	maxProjA *= A.GetWorld().get(MatrixRowType::ROW_0).magSqr(); // assuming uniform scaling? 

	// max projection of b onto v

	Vect locAxisB = axis;

	float maxProjB = (abs(locAxisB.X() * B.GetLocalHalfDiagonal().X()) + abs(locAxisB.Y() * B.GetLocalHalfDiagonal().Y()) + abs(locAxisB.Z() * B.GetLocalHalfDiagonal().Z())) / axis.mag();
	//maxProjB *= B.GetWorld().get(MatrixRowType::ROW_0).magSqr();

	// calculate D

	float D = abs((B.GetCenter() - A.GetCenter()).dot(axis)) / axis.mag();

	//DataLogger::Add("ProjA:  %f  ProjB:  %f  D:  %f", maxProjA, maxProjB, D);

	return D <= maxProjA + maxProjB;

}

bool SMathTools::PointIntersectOBB(const Vect& point, const CollisionVolumeOBB& B)
{
	Vect localPoint = point * B.GetWorld().getInv();
	Vect clampedPoint;

	return ValueWithinInterval(point.X(), B.GetLocMin().X(), B.GetLocMax().X()) &&
		ValueWithinInterval(point.Y(), B.GetLocMin().Y(), B.GetLocMax().Y()) &&
		ValueWithinInterval(point.Z(), B.GetLocMin().Z(), B.GetLocMax().Z());
}

bool SMathTools::IntersectBSphereOBB(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B)
{
	// move point into local space
	Vect BSPoint = A.GetCenter();
	BSPoint = BSPoint * B.GetWorld().getInv(); // move point into local space 
	Vect clampedPoint;

	clampedPoint.X() = Clamp(BSPoint.X(), B.GetLocMin().X(), B.GetLocMax().X());
	clampedPoint.Y() = Clamp(BSPoint.Y(), B.GetLocMin().Y(), B.GetLocMax().Y());
	clampedPoint.Z() = Clamp(BSPoint.Z(), B.GetLocMin().Z(), B.GetLocMax().Z());

	// move clamped point back into world space
	Vect wsPoint = clampedPoint * B.GetWorld();

	return PointIntersectBSphere(wsPoint, A);
}

bool SMathTools::IntersectAABBOBB( const CollisionVolumeOBB& A, const CollisionVolumeAABB& B)
{

	// compute axis to project 
	// 3 face normals for A 
	// 3 face normals for B
	// 3x3 cross products of above

	// A face normals
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_0), A, B)) return false;
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_1), A, B)) return false;
	if (!AxisTest(A.GetWorld().get(MatrixRowType::ROW_2), A, B)) return false;
	// B face normals
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_0), A, B)) return false;
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_1), A, B)) return false;
	if (!AxisTest(B.GetWorld().get(MatrixRowType::ROW_2), A, B)) return false;

	// cross products
	// 
	// A0 x B0
	Vect Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A0 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A0 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_0).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B0
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A1 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_1).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B0
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_0));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B1
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_1));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}
	// A2 x B2
	Axis = A.GetWorld().get(MatrixRowType::ROW_2).cross(B.GetWorld().get(MatrixRowType::ROW_2));
	if (Axis.magSqr() > FLT_EPSILON)
	{
		if (!AxisTest(Axis, A, B))return false;
	}

	return true;

}

bool SMathTools::IntervalIntersection(const float intervalAMin, const float intervalAMax, const float intervalBMin, const float intervalBMax)
{
	return !(intervalAMax < intervalBMin || intervalBMax < intervalAMin); 
}

float SMathTools::Clamp(const float value, const float rangeMin, const float rangeMax)
{
	if (value < rangeMin) return rangeMin;
	else if (value > rangeMax) return rangeMax;
	else return value;
}

int SMathTools::Clamp(const int value, const int rangeMin, const int rangeMax)
{
	if (value < rangeMin) return rangeMin;
	else if (value > rangeMax) return rangeMax;
	else return value;
}

bool SMathTools::ValueWithinInterval(const float value, const float rangeMin, const float rangeMax)
{
	return (value >= rangeMin) && (value <= rangeMax);
}

Vect SMathTools::VectAbs(const Vect& A)
{
	Vect out;
	out.X() = abs(A.X());
	out.Y() = abs(A.Y());
	out.Z() = abs(A.Z());
	out.W() = abs(A.W());
	return out;
}

Vect SMathTools::ProjVect(const Vect& A, const Vect& alongB)
{
	return (A.dot(alongB) / alongB.dot(alongB)) * alongB;
}


Vect SMathTools::MinVect(const Vect& A, const Vect& B)
{

	Vect out = A;

	if (B.X() < out.X()) out.X() = B.X();
	if (B.Y() < out.Y()) out.Y() = B.Y();
	if (B.Z() < out.Z()) out.Z() = B.Z();
	if (B.W() < out.W()) out.W() = B.W();

	return out;
}

Vect SMathTools::MaxVect(const Vect& A, const Vect& B)
{
	Vect out = A;

	if (B.X() > out.X()) out.X() = B.X();
	if (B.Y() > out.Y()) out.Y() = B.Y();
	if (B.Z() > out.Z()) out.Z() = B.Z();
	if (B.W() > out.W()) out.W() = B.W();

	return out;
}