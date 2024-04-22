// game object

#include "GameObject.h"
#include <assert.h>
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

GameObject::GameObject()
{
	ptrEntryCmd = nullptr;
	ptrExitCmd = nullptr;
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
}

GameObject::~GameObject()
{
	delete ptrEntryCmd;
	delete ptrExitCmd;
}

void GameObject::ConnectToScene()
{
 	assert(currentState == RegistrationState::PENDING_REGISTRATION);

	currentState = RegistrationState::CURRENTLY_REGISTERED;
	this->SceneEntry(); // call user method
}

void GameObject::DisconnectFromScene()
{
	currentState = RegistrationState::CURRENTLY_DEREGISTERED;
	this->SceneExit(); // user method
}

void GameObject::SubmitEntry()
{
	assert(currentState == RegistrationState::CURRENTLY_DEREGISTERED);

	if (!ptrEntryCmd)
	{
		ptrEntryCmd = new GameObjectEntryCommand(this);
		ptrExitCmd = new GameObjectExitCommand(this);
	}

	currentState = RegistrationState::PENDING_REGISTRATION;
	//SceneManager::GetCurrentScene()->SubmitCommand(ptrEntryCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), ptrEntryCmd);
}

void GameObject::SubmitExit()
{
	if (currentState == RegistrationState::CURRENTLY_REGISTERED) // only call this once even if submit is called many times 
	{
 		assert(ptrExitCmd); // double check we have an exit command
		currentState = RegistrationState::PENDING_DEREGISTRATION;
		//SceneManager::GetCurrentScene()->SubmitCommand(ptrExitCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), ptrExitCmd);
	}

}

// user defined methods 
void GameObject::SceneEntry()
{
	// do nothing
}

void GameObject::SceneExit()
{
	// do nothing
}