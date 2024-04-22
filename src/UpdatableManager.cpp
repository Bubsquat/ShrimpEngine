// Manager for registering if an object should be updated 

#include "UpdatableManager.h"
#include "Updatable.h"
#include <assert.h>

void UpdatableManager::Register(Updatable* obj)
{
	this->updateList.push_back(obj);
}

void UpdatableManager::Deregister(Updatable* obj)
{
	this->updateList.remove(obj);
}

void UpdatableManager::ProcessElements()
{
	for (UpdateList::iterator it = updateList.begin(); it != updateList.end(); it++)
	{
		(*it)->Update();
	}
}

UpdatableManager::~UpdatableManager()
{

	this->updateList.clear();

}