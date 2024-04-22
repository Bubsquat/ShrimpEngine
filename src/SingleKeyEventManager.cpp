// manager responsible for monitoring the state of a single key 

#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"
#include <assert.h>
#include "KeyboardEvents.h"


SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
	:key(k), prevKeyState(KEY_STATES::KEY_UP), currKeyState(KEY_STATES::KEY_UP)
{}

SingleKeyEventManager::~SingleKeyEventManager()
{
	keyPress.clear();
	keyReleased.clear();
	keyHolding.clear();
	keyReleased.clear();
}

void SingleKeyEventManager::ProcessKeyEvent()
{

	// get current key state and update previous key state 
	prevKeyState = currKeyState;
	currKeyState = static_cast<KEY_STATES>(static_cast<int>(Keyboard::GetKeyState(key)));
	// line above converts the bool of keyboard into an int then a keystate 
	// depended on the ordering of the keystate enum being up then down 


	switch (currKeyState) // this ugly switch can probably be replaced with commands later 
	{
	case KEY_STATES::KEY_UP:

		switch (prevKeyState)
		{
		case KEY_STATES::KEY_UP:
			// key not held event 
			this->handleKeyNotHolding();
			break;

		case KEY_STATES::KEY_DOWN:
			// Key pressed event
			this->handleKeyPress();
			break;

		default:
			assert("error");
			break;
		}

		break;

	case KEY_STATES::KEY_DOWN:

		switch (prevKeyState)
		{
		case KEY_STATES::KEY_DOWN:
			// key held event
			this->handleKeyHolding();
			break;
			
		case KEY_STATES::KEY_UP:
			// key released event
			this->handleKeyRelease();
			break;

		default:
			assert("error");
			break;
		}

		break;

	default:
		assert("Error No KeyState Reported");
	}

}

void SingleKeyEventManager::Register(Inputable* obj, KeyboardEvents ev)
{

	switch (ev) // another gross switch but this isnt done at runtime at least
	{
	case KeyboardEvents::KEY_PRESS:

		InputableAttorney::GameLoop::SetDeleteRef(obj, keyPress.insert(keyPress.end(), obj));
		break;

	case KeyboardEvents::KEY_RELEASE:

		InputableAttorney::GameLoop::SetDeleteRef(obj, keyReleased.insert(keyReleased.end(), obj));
		break;
		
	case KeyboardEvents::KEY_HOLDING:

		InputableAttorney::GameLoop::SetDeleteRef(obj, keyHolding.insert(keyHolding.end(), obj));
		break;

	case KeyboardEvents::KEY_NOT_HELD:

		InputableAttorney::GameLoop::SetDeleteRef(obj, keyNotHolding.insert(keyNotHolding.end(), obj));
		break;

	default:
		assert("error");
		break;
	}

	// might need to do registration states here? probably not tho

}

void SingleKeyEventManager::Deregister(Inputable* obj, KeyboardEvents ev) // this is wrong, its deleting the entire inputable unecessarily 
{

	switch (ev) // another gross switch but this isnt done at runtime at least
	{
	case KeyboardEvents::KEY_PRESS:

		keyPress.remove(obj);
		break;

	case KeyboardEvents::KEY_RELEASE:

		keyReleased.remove(obj);
		break;

	case KeyboardEvents::KEY_HOLDING:

		keyHolding.remove(obj);
		break;

	case KeyboardEvents::KEY_NOT_HELD:

		keyNotHolding.remove(obj);
		break;

	default:
		assert("error");
		break;
	}

}

void SingleKeyEventManager::handleKeyPress()
{
	InputListRef it = keyPress.begin();

	while (it != keyPress.end())
	{
		(*it)->KeyPressed(key);
		it++;
	}
}

void SingleKeyEventManager::handleKeyRelease()
{
	InputListRef it = keyReleased.begin();

	while (it != keyReleased.end())
	{
		(*it)->KeyReleased(key);
		it++;
	}
}

void SingleKeyEventManager::handleKeyHolding()
{
	InputListRef it = keyHolding.begin();

	while (it != keyHolding.end())
	{
		(*it)->KeyHolding(key);
		it++;
	}
}

void SingleKeyEventManager::handleKeyNotHolding()
{
	InputListRef it = keyNotHolding.begin();

	while (it != keyNotHolding.end())
	{
		(*it)->KeyNotHolding(key);
		it++;
	}
}
