// manager for checking each active single key manager

#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"
#include <assert.h>



KeyboardEventManager::~KeyboardEventManager()
{
	for (KeyManagerMap::iterator it = keyManagers.begin(); it != keyManagers.end(); it++)
	{
		delete (*it).second;
	}

	keyManagers.clear();
}

void KeyboardEventManager::Register(Inputable* obj, AZUL_KEY k, KeyboardEvents ev)
{
	// check if a manager exists for the key 

	KeyManagerMap::iterator item = keyManagers.find(k);

	if (item == keyManagers.end()) // create a new manager for that key 
	{
		KeyMapItem newManager = { k, new SingleKeyEventManager(k) };
		keyManagers.insert(newManager);
		newManager.second->Register(obj, ev);
	} 
	else 
	{
		(*item).second->Register(obj, ev);
	}

}

void KeyboardEventManager::Deregister(Inputable* obj, AZUL_KEY k, KeyboardEvents ev)
{

	KeyManagerMap::iterator item = keyManagers.find(k);
	assert(item != keyManagers.end()); // make sure item exists 
	(*item).second->Deregister(obj, ev);

}

void KeyboardEventManager::ProcessKeyEvents()
{

	for (KeyManagerMap::iterator it = keyManagers.begin(); it != keyManagers.end(); it++)
	{
		(*it).second->ProcessKeyEvent();
	}

}