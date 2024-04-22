// command for deregistering update Deregistration 

#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "RegistrationCommand.h"

class Updateable;

class UpdateDeregistrationCommand : public RegistrationCommand
{
public:

	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(Updateable* cmd);
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator =(const UpdateDeregistrationCommand&) = delete;
	~UpdateDeregistrationCommand() = default;

	void execute();

private:

	Updateable* ptrUpdateable;

};



#endif _UpdateDeregistrationCommand
