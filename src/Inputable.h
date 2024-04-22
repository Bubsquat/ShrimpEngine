// attribute that allows a game object to recieve keyboard input

#ifndef _Inputable
#define _Inputable

#include "AzulCore.h"
#include "KeyboardEvents.h"
#include "SingleKeyEventManager.h"
#include "RegistrationStateEnum.h"
#include <map>

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;
public:

	Inputable() = default;
	Inputable(const Inputable&) = delete;
	Inputable& operator =(const Inputable&) = delete;
	~Inputable();

	virtual void KeyPressed(AZUL_KEY k); // user defined 
	virtual void KeyReleased(AZUL_KEY k);
	virtual void KeyHolding(AZUL_KEY k);
	virtual void KeyNotHolding(AZUL_KEY k);

	void SubmitKeyRegistration(AZUL_KEY k, KeyboardEvents ev);
	void SubmitKeyDeregistration(AZUL_KEY k, KeyboardEvents ev);

private:

	SingleKeyEventManager::InputListRef myDeleteRef;

	struct RegDereg
	{
		InputRegistrationCommand* regCmd;
		InputDeregistrationCommand* deregCmd;
		RegistrationState CmdState;
	};

	using KeyRegCmdPair = std::pair<AZUL_KEY, RegDereg>;
	using RegistrationMap = std::map<AZUL_KEY, RegDereg>;
	
	RegistrationMap keyPressedReg;
	RegistrationMap keyReleasedReg;
	RegistrationMap keyHoldingReg;
	RegistrationMap keyNotHoldingReg;

	void SetDeleteRef(SingleKeyEventManager::InputListRef ref);
	SingleKeyEventManager::InputListRef GetDeleteRef();
	void SceneRegistration(AZUL_KEY k, KeyboardEvents ev);
	void SceneDeregistration(AZUL_KEY k, KeyboardEvents ev);

};


#endif _Inputable
