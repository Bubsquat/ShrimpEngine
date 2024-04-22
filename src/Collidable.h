// attribute that allows an object to have collision 

#ifndef _Collidable
#define _Collidable

enum class RegistrationState;
class CollidableRegistrationCommand;
class CollidableDeregistrationCommand;
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;

#include "CollisionManager.h"
#include "SceneAttorney.h"
#include "CollidableGroup.h"

class Collidable
{
	friend class CollidableAttorney;
public:

	enum VOLUME_TYPE
	{
		BSPHERE,
		AABB,
		OBB
	};

	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;
	~Collidable();

	void SubmitCollisionRegistration();
	void SubmitCollisionDeregistration();
	
	void UpdateCollisionData(const Matrix& mat);
	void SetColliderModel(Model* mod, VOLUME_TYPE type);
	const CollisionVolume& GetCollisionVolume();
	const CollisionVolumeBSphere& GetDefaultBSphere();

private:
	
	RegistrationState currentState;
	CollidableRegistrationCommand* regCmd;
	CollidableDeregistrationCommand* deregCmd;

	void SceneRegistration();
	void SceneDeregistration();
	CollidableGroup::CollidableCollectionRef GetDeleteRef();
	void SetDeleteRef(CollidableGroup::CollidableCollectionRef ref);
	CollisionManager::STypeID GetTypeId();

	CollisionManager::STypeID myID = CollisionManager::SID_UNDEFINED;
	CollidableGroup::CollidableCollectionRef deleteRef; 

	CollisionVolumeBSphere* defaultBSphere;
	CollisionVolume* pColVolume;
	
	Model* pColModel;

protected:
	template <typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::Registration::GetCollisionMgr(SceneManager::GetCurrentScene())->GetTypeID<C>();
	}

};

#endif _Collidable
