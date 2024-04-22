// Bsphere for collision 

#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"

class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolumeBSphere : public CollisionVolume
{
public:

	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	CollisionVolumeBSphere& operator= (const CollisionVolumeBSphere&) = delete;
	~CollisionVolumeBSphere() = default;

	void ComputeData(Model* mod, const Matrix& mat);
	void DebugView(const Vect& col) const;
	const Vect& GetCenter() const;
	float GetRadius() const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeOBB& other) const;

private:

	Vect Center;
	float Radius;
};

#endif _CollisionVolumeBSphere
