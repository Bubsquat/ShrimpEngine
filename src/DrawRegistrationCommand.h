// command for updating draw registration 

#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "RegistrationCommand.h"

class Drawable;

class DrawRegistrationCommand : public RegistrationCommand
{
public:

	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(Drawable* cmd);
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator =(const DrawRegistrationCommand&) = delete;
	~DrawRegistrationCommand() = default;

	void execute();

private:

	Drawable* ptrDrawable;

};



#endif _DrawRegistrationCommand
