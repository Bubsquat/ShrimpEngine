// manager responsible for monitoring the state of a single key 

#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

class Inputable;
#include "AzulCore.h"
#include "KeyboardEvents.h"
#include <list>

class SingleKeyEventManager
{
public:

	SingleKeyEventManager() = delete;
	SingleKeyEventManager(AZUL_KEY k);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator = (const SingleKeyEventManager &) = delete;
	~SingleKeyEventManager();

	void Register(Inputable* obj, KeyboardEvents ev);
	void Deregister(Inputable* obj, KeyboardEvents ev);
	void ProcessKeyEvent();

	enum class KEY_STATES
	{
		// entry order matters here 
		KEY_UP,
		KEY_DOWN
	};

private:

	AZUL_KEY key;
	KEY_STATES prevKeyState;
	KEY_STATES currKeyState;

	using InputList = std::list<Inputable*>;

	InputList keyPress;
	InputList keyReleased;
	InputList keyHolding;
	InputList keyNotHolding;

	// functions seperated for readability 

	void handleKeyPress();
	void handleKeyRelease();
	void handleKeyHolding();
	void handleKeyNotHolding();

public:

	using InputListRef = InputList::iterator;

};



#endif _SingleKeyEventManager
