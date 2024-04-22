// Manager for registering if an object should be updated 

#include "UpdateableManager.h"
#include "UpdateableAttorney.h"
#include <assert.h>
#include "RegistrationStateEnum.h"

void UpdateableManager::Register(Updateable* obj)
{
	UpdateableAttorney::GameLoop::SetListRef(obj, updateList.insert(updateList.end(), obj));
}

void UpdateableManager::Deregister(Updateable* obj)
{
	updateList.erase(UpdateableAttorney::GameLoop::GetListRef(obj));
}

void UpdateableManager::ProcessElements()
{
	for (UpdateList::iterator it = updateList.begin(); it != updateList.end(); it++)
	{
		UpdateableAttorney::GameLoop::Update((*it));
	}
}

UpdateableManager::~UpdateableManager()
{
	this->updateList.clear();
}