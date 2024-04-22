// attribute that allows a game object to be updated 

#include "Drawable.h"
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "RegistrationStateEnum.h"
#include <assert.h>
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

Drawable::Drawable()
{
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegCmd = new DrawRegistrationCommand(this);
	pDeregCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{
	delete pRegCmd;
	delete pDeregCmd;
}

void Drawable::SubmitDrawRegistration()
{
	assert(currentState == RegistrationState::CURRENTLY_DEREGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pRegCmd);
	currentState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(currentState == RegistrationState::CURRENTLY_REGISTERED);
	//SceneManager::GetCurrentScene()->SubmitCommand(pDeregCmd); 
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), pDeregCmd);
	currentState = RegistrationState::PENDING_DEREGISTRATION; 
}

void Drawable::SceneRegistration()
{
	assert(currentState == RegistrationState::PENDING_REGISTRATION);
	//SceneManager::GetCurrentScene()->Register(this);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this);
	currentState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(currentState == RegistrationState::PENDING_DEREGISTRATION); 
	//SceneManager::GetCurrentScene()->Deregister(this);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), this);
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
}

DrawableManager::DrawListRef Drawable::GetListRef()
{
	return this->pMyDeleteRef;
}

void Drawable::SetListRef(DrawableManager::DrawListRef ref)
{
	this->pMyDeleteRef = ref; 
}

void Drawable::SetRegistrationState(RegistrationState state)
{
	currentState = state;
}

// user meathods 

void Drawable::Draw()
{
	// do nothing 
}

void Drawable::Draw2D()
{
	// do nothing 
}