// manager for checking each active single key manager

#ifndef _KeyboardEventManager
#define _KeyboardEventManager

class Inputable;
class SingleKeyEventManager;
#include "AzulCore.h"
#include "KeyboardEvents.h"
#include <map>

class KeyboardEventManager
{
public:

	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator =(const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	void Register(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	void Deregister(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	void ProcessKeyEvents();

private:

	using KeyManagerMap = std::map<AZUL_KEY, SingleKeyEventManager*>;
	using KeyMapItem = std::pair<AZUL_KEY, SingleKeyEventManager*>;
	KeyManagerMap keyManagers;

};



#endif _KeyboardEventManager
