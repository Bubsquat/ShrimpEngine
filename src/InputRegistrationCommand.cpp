// command for updating input registration 

#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"
#include "KeyboardEvents.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* _obj, AZUL_KEY _k, KeyboardEvents _ev)
	:ptrInputable(_obj), key(_k), ev(_ev)
{}

void InputRegistrationCommand::execute()
{
	InputableAttorney::Registration::SceneRegistration(ptrInputable, key, ev);
}