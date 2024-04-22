// oriented bounding box for collisision testing 

#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolume.h"



class CollisionVolumeOBB : public CollisionVolume
{
public:

	CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = delete;
	~CollisionVolumeOBB() = default;

	void ComputeData(Model* mod, const Matrix& mat);
	void DebugView(const Vect& col) const;

	bool IntersectAccept(const CollisionVolume& other) const;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const;
	bool IntersectVisit(const CollisionVolumeAABB& other) const; 
	bool IntersectVisit(const CollisionVolumeOBB& other) const;

	const Vect& GetCenter() const;
	const Vect& GetLocMin() const;
	const Vect& GetLocMax() const;
	const Vect& GetLocalHalfDiagonal() const;
	const Matrix& GetWorld() const;
	//const Vect& GetScale() const;

private:

	Vect locMin;
	Vect locMax;
	//Vect scale;
	Vect locHalfDiagonal;
	Vect center;
	Matrix world;
};


#endif _CollisionVolumeOBB
