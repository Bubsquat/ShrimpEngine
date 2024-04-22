// command for updating collision registration

#ifndef _CollidableRegistrationCommand
#define _CollidableRegistrationCommand

#include "RegistrationCommand.h"
class Collidable;

class CollidableRegistrationCommand : public RegistrationCommand
{
public:
	CollidableRegistrationCommand() = delete;
	CollidableRegistrationCommand(Collidable* obj);
	CollidableRegistrationCommand(const CollidableRegistrationCommand&) = delete;
	CollidableRegistrationCommand& operator=(const CollidableRegistrationCommand&) = delete;
	~CollidableRegistrationCommand() = default;

	void execute();

private:
	Collidable* ptrCollidable;
};

#endif _CollidableRegistrationCommand
