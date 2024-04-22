// command for updating input Deregistration 

#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"
#include "KeyboardEvents.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* _obj, AZUL_KEY _k, KeyboardEvents _ev)
	:ptrInputable(_obj), key(_k), ev(_ev)
{}

void InputDeregistrationCommand::execute()
{
	InputableAttorney::Registration::SceneDeregistration(ptrInputable, key, ev);
}