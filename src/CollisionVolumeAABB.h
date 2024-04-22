// collision volume for axis aligned bounding box

#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolume.h"

class CollisionVolumeBSphere;
class CollisionVolumeOBB;

class CollisionVolumeAABB : public CollisionVolume
{
public:

	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = delete;
	CollisionVolumeAABB& operator= (const CollisionVolumeAABB&) = delete;
	~CollisionVolumeAABB() = default;

	void ComputeData(Model * mod, const Matrix & mat);
	void ComputeData(const CollisionVolumeBSphere& bs);
	void DebugView(const Vect & col) const;
	const Vect& GetMin() const;
	const Vect& GetMax() const;
	void SetMin(Vect min);
	void SetMax(Vect max);
	const Vect& GetLocalHalfDiagonal() const;
	const Matrix& GetWorld() const;
	const Vect& GetCenter() const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeOBB& other) const;

private:

	Vect center;
	Matrix world = Matrix(IDENTITY);
	Vect Min;
	Vect Max;
	Vect locHalfDiagonal;
};

#endif _CollisionVolumeAABB
