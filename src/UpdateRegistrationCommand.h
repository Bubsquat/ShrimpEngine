// command for updating update registration 

#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "RegistrationCommand.h"

class Updateable;

class UpdateRegistrationCommand : public RegistrationCommand
{
public:

	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(Updateable* cmd);
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator =(const UpdateRegistrationCommand&) = delete;
	~UpdateRegistrationCommand() = default;

	void execute();

private:

	Updateable* ptrUpdateable; 

};



#endif _UpdateRegistrationCommand
