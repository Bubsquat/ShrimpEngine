// command for updating input Deregistration 

#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "RegistrationCommand.h"
#include "AzulCore.h"
#include "KeyboardEvents.h"

class Inputable;

class InputDeregistrationCommand : public RegistrationCommand
{
public:

	InputDeregistrationCommand() = delete;
	InputDeregistrationCommand(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	InputDeregistrationCommand(const InputDeregistrationCommand&) = delete;
	InputDeregistrationCommand& operator =(const InputDeregistrationCommand&) = delete;
	~InputDeregistrationCommand() = default;

	void execute();

private:

	Inputable* ptrInputable;
	AZUL_KEY key;
	KeyboardEvents ev;
};



#endif _InputDeregistrationCommand