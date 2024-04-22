// attribute that allows a game object to be updateable 

#include "Updateable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include <assert.h>
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "RegistrationStateEnum.h"

Updateable::Updateable()
{
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegCmd = new UpdateRegistrationCommand(this);
	pDeregCmd = new UpdateDeregistrationCommand(this);
}

Updateable::~Updateable()
{
	delete pRegCmd;
	delete pDeregCmd;
}

void Updateable::Update()
{

}

void Updateable::SceneRegistration()
{
	assert(currentState == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register(this);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this);
	currentState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updateable::SceneDeregistration()
{
	assert(currentState == RegistrationState::PENDING_DEREGISTRATION);
	//SceneManager::GetCurrentScene()->Deregister(this);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), this);
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updateable::SubmitUpdateRegistration()
{
	assert(currentState == RegistrationState::CURRENTLY_DEREGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pRegCmd);
	currentState = RegistrationState::PENDING_REGISTRATION;
}

void Updateable::SubmitUpdateDeregistration()
{
	assert(currentState == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pDeregCmd);
	currentState = RegistrationState::PENDING_DEREGISTRATION;
}

UpdateableManager::UpdateListRef Updateable::GetListRef()
{
	return this->pMyDeleteRef;
}

void Updateable::SetListRef(UpdateableManager::UpdateListRef ref)
{
	this->pMyDeleteRef = ref; 
}

void Updateable::SetRegistrationState(RegistrationState state)
{
	currentState = state; 
}