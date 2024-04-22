// attribute that allows an object to have collision 

#include "Collidable.h"
#include "RegistrationStateEnum.h"
#include "SceneManager.h"
#include "CollidableRegistrationCommand.h"
#include "CollidableDeregistrationCommand.h"
#include "CollisionVolume.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

Collidable::Collidable()
{
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
	regCmd = new CollidableRegistrationCommand(this);
	deregCmd = new CollidableDeregistrationCommand(this);
	defaultBSphere = new CollisionVolumeBSphere();
	pColModel = nullptr;
	pColVolume = nullptr;
}

Collidable::~Collidable()
{
	delete regCmd;
	delete deregCmd;
	if (pColVolume) delete pColVolume; // collision volume may not be set so we need to check if it exists 
	delete defaultBSphere;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(currentState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), regCmd);
	currentState = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(currentState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), deregCmd);
	currentState = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::SceneRegistration()
{
	assert(currentState == RegistrationState::PENDING_REGISTRATION);
	
	SceneAttorney::Registration::GetCollisionMgr(SceneManager::GetCurrentScene())->GetColGroup(myID)->Register(this);
	currentState = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(currentState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::GetCollisionMgr(SceneManager::GetCurrentScene())->GetColGroup(myID)->Deregister(deleteRef);
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::SetDeleteRef(CollidableGroup::CollidableCollectionRef ref)
{
	this->deleteRef = ref;
}

CollidableGroup::CollidableCollectionRef Collidable::GetDeleteRef()
{
	return this->deleteRef;
}

CollisionManager::STypeID Collidable::GetTypeId()
{
	return myID;
}

void Collidable::SetColliderModel(Model* mod, VOLUME_TYPE type)
{
	this->pColModel = mod;

	switch (type)
	{
	case VOLUME_TYPE::BSPHERE :
		pColVolume = new CollisionVolumeBSphere();
		break;
	case VOLUME_TYPE::AABB :
		pColVolume = new CollisionVolumeAABB();
		break;
	case VOLUME_TYPE::OBB :
		pColVolume = new CollisionVolumeOBB();
		break;

	default:
		assert("Error on setting collider model!");
		break;
	}
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	//BSphere.ComputeData(pColModel, mat);
	pColVolume->ComputeData(pColModel, mat);
	defaultBSphere->ComputeData(pColModel, mat);
}

const CollisionVolume& Collidable::GetCollisionVolume()
{
	return *pColVolume;
}

const CollisionVolumeBSphere& Collidable::GetDefaultBSphere()
{
	return *defaultBSphere;
}
