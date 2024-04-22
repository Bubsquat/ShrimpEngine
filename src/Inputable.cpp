// attribute that allows a game object to recieve keyboard input

#include "Inputable.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
#include "RegistrationStateEnum.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

Inputable::~Inputable()
{

	for (RegistrationMap::iterator it = keyPressedReg.begin(); it != keyPressedReg.end(); it++)
	{
		delete (*it).second.regCmd;
		delete (*it).second.deregCmd;
	}
	keyPressedReg.clear();

	for (RegistrationMap::iterator it = keyReleasedReg.begin(); it != keyReleasedReg.end(); it++)
	{
		delete (*it).second.regCmd;
		delete (*it).second.deregCmd;
	}
	keyReleasedReg.clear();

	for (RegistrationMap::iterator it = keyHoldingReg.begin(); it != keyHoldingReg.end(); it++)
	{
		delete (*it).second.regCmd;
		delete (*it).second.deregCmd;
	}
	keyHoldingReg.clear();

	for (RegistrationMap::iterator it = keyNotHoldingReg.begin(); it != keyNotHoldingReg.end(); it++)
	{
		delete (*it).second.regCmd;
		delete (*it).second.deregCmd;
	}
	keyNotHoldingReg.clear();

}


void Inputable::SceneRegistration(AZUL_KEY k, KeyboardEvents ev)
{
	//SceneManager::GetCurrentScene()->Register(this, k, ev);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this, k, ev);
}

void Inputable::SceneDeregistration(AZUL_KEY k, KeyboardEvents ev)
{
	//SceneManager::GetCurrentScene()->Deregister(this, k, ev);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), this, k, ev);
}

void Inputable::SubmitKeyRegistration(AZUL_KEY k, KeyboardEvents ev)
{
	
	RegistrationMap::iterator found;

	switch (ev)
	{
	case KeyboardEvents::KEY_PRESS:

		found = keyPressedReg.find(k);

		if (found == keyPressedReg.end()) // command doesnt exist 
		{
			RegDereg newCommands;
			newCommands.regCmd = new InputRegistrationCommand(this, k, ev);
			newCommands.deregCmd = new InputDeregistrationCommand(this, k, ev); // might as well create a deregistration command here 
			newCommands.CmdState = RegistrationState::CURRENTLY_REGISTERED;
			keyPressedReg.emplace(k, newCommands);

			//SceneManager::GetCurrentScene()->SubmitCommand(newCommands.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), newCommands.regCmd);
		}
		else // command exists, send em
		{
			assert((*found).second.CmdState == RegistrationState::CURRENTLY_DEREGISTERED);
			//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.regCmd);
			(*found).second.CmdState = RegistrationState::CURRENTLY_REGISTERED;
		}

		break;

	case KeyboardEvents::KEY_RELEASE:

		found = keyReleasedReg.find(k);

		if (found == keyReleasedReg.end()) // command doesnt exist 
		{
			RegDereg newCommands;
			newCommands.regCmd = new InputRegistrationCommand(this, k, ev);
			newCommands.deregCmd = new InputDeregistrationCommand(this, k, ev);
			newCommands.CmdState = RegistrationState::CURRENTLY_REGISTERED;
			keyReleasedReg.emplace(k, newCommands);
			//SceneManager::GetCurrentScene()->SubmitCommand(newCommands.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), newCommands.regCmd);
		}
		else // command exists, send em
		{
			assert((*found).second.CmdState == RegistrationState::CURRENTLY_DEREGISTERED);
			//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.regCmd);
			(*found).second.CmdState = RegistrationState::CURRENTLY_REGISTERED;
		}
		break;

	case KeyboardEvents::KEY_HOLDING:

		found = keyHoldingReg.find(k);

		if (found == keyHoldingReg.end()) // command doesnt exist 
		{
			RegDereg newCommands;
			newCommands.regCmd = new InputRegistrationCommand(this, k, ev);
			newCommands.deregCmd = new InputDeregistrationCommand(this, k, ev);
			newCommands.CmdState = RegistrationState::CURRENTLY_REGISTERED;
			keyHoldingReg.emplace(k, newCommands);
			//SceneManager::GetCurrentScene()->SubmitCommand(newCommands.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), newCommands.regCmd);
		}
		else // command exists, send em
		{
			assert((*found).second.CmdState == RegistrationState::CURRENTLY_DEREGISTERED);
			//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.regCmd);
			(*found).second.CmdState = RegistrationState::CURRENTLY_REGISTERED;
		}
		break;

	case KeyboardEvents::KEY_NOT_HELD:

		found = keyNotHoldingReg.find(k);

		if (found == keyNotHoldingReg.end()) // command doesnt exist 
		{
			RegDereg newCommands;
			newCommands.regCmd = new InputRegistrationCommand(this, k, ev);
			newCommands.deregCmd = new InputDeregistrationCommand(this, k, ev);
			newCommands.CmdState = RegistrationState::CURRENTLY_REGISTERED;
			keyNotHoldingReg.emplace(k, newCommands);
			//SceneManager::GetCurrentScene()->SubmitCommand(newCommands.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), newCommands.regCmd);
		}
		else // command exists, send em
		{
			assert((*found).second.CmdState == RegistrationState::CURRENTLY_DEREGISTERED);
			//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.regCmd);
			SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.regCmd);
			(*found).second.CmdState = RegistrationState::CURRENTLY_REGISTERED;
		}

		break;

	default:
		assert("switch fail in key registration"); 
			break;
	}

}

void Inputable::SubmitKeyDeregistration(AZUL_KEY k, KeyboardEvents ev)
{

	RegistrationMap::iterator found;

	switch (ev)
	{
	case KeyboardEvents::KEY_PRESS:

		found = keyPressedReg.find(k);
		assert(found != keyPressedReg.end()); // make sure a command exists 
		(*found).second.CmdState = RegistrationState::CURRENTLY_DEREGISTERED;
		//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.deregCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.deregCmd);
		break;

	case KeyboardEvents::KEY_RELEASE:

		found = keyReleasedReg.find(k);
		assert(found != keyReleasedReg.end()); // make sure a command exists 
		(*found).second.CmdState = RegistrationState::CURRENTLY_DEREGISTERED;
		//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.deregCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.deregCmd);
		break;
		
	case KeyboardEvents::KEY_HOLDING:

		found = keyHoldingReg.find(k);
		assert(found != keyHoldingReg.end()); // make sure a command exists 
		(*found).second.CmdState = RegistrationState::CURRENTLY_DEREGISTERED;
		//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.deregCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.deregCmd);
		break;

	case KeyboardEvents::KEY_NOT_HELD:

		found = keyNotHoldingReg.find(k);
		assert(found != keyNotHoldingReg.end()); // make sure a command exists 
		(*found).second.CmdState = RegistrationState::CURRENTLY_DEREGISTERED;
		//SceneManager::GetCurrentScene()->SubmitCommand((*found).second.deregCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), (*found).second.deregCmd);
		break;
	}

}

void Inputable::SetDeleteRef(SingleKeyEventManager::InputListRef ref)
{
	this->myDeleteRef = ref;
}

SingleKeyEventManager::InputListRef Inputable::GetDeleteRef()
{
	return this->myDeleteRef;
}


// user defined functions 

void Inputable::KeyPressed(AZUL_KEY k)
{
	k;
	// do nothing
}

void Inputable::KeyReleased(AZUL_KEY k)
{
	k;
	// do nothing 
}

void Inputable::KeyHolding(AZUL_KEY k)
{
	k;
	// do nothing 
}

void Inputable::KeyNotHolding(AZUL_KEY k)
{
	k;
	// do nothing
}