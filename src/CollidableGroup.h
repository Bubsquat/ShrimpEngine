// group of collidable objects of a type 

#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

class Collidable;
class CollisionVolumeAABB;

class CollidableGroup
{
public:

	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator= (const CollidableGroup&) = delete;
	~CollidableGroup();

	using CollidableCollection = std::list<Collidable*>;
	using CollidableCollectionRef = CollidableCollection::iterator;

	const CollidableCollection& GetColliderCollection();
	void Register(Collidable* obj);
	void Deregister(CollidableCollectionRef ref);

	// collision optimization
	const CollisionVolumeAABB& GetGroupAABB();
	void UpdateGroupCollision();

private:
	CollidableCollection collidableCollection;
	CollisionVolumeAABB* collidableGroupAABB;
};

#endif _CollidableGroup
