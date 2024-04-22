// command for updating input registration 

#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "RegistrationCommand.h"
#include "AzulCore.h"
#include "KeyboardEvents.h"

class Inputable;

class InputRegistrationCommand : public RegistrationCommand
{
public:

	InputRegistrationCommand() = delete;
	InputRegistrationCommand(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	InputRegistrationCommand(const InputRegistrationCommand&) = delete;
	InputRegistrationCommand& operator =(const InputRegistrationCommand&) = delete;
	~InputRegistrationCommand() = default;

	void execute();

private:

	Inputable* ptrInputable;
	AZUL_KEY key;
	KeyboardEvents ev;
};



#endif _InputRegistrationCommand
