// command for updating draw Deregistration 

#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "RegistrationCommand.h"

class Drawable;

class DrawDeregistrationCommand : public RegistrationCommand
{
public:

	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(Drawable* cmd);
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator =(const DrawDeregistrationCommand&) = delete;
	~DrawDeregistrationCommand() = default;

	void execute();

private:

	Drawable* ptrDrawable;

};



#endif _DrawDeregistrationCommand
