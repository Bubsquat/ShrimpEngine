// command for updating collision deregistration

#ifndef _CollidableDeregistrationCommand
#define _CollidableDeregistrationCommand

#include "RegistrationCommand.h"

class Collidable;

class CollidableDeregistrationCommand : public RegistrationCommand
{
public:
	CollidableDeregistrationCommand() = delete;
	CollidableDeregistrationCommand(Collidable* obj);
	CollidableDeregistrationCommand(const CollidableDeregistrationCommand&) = delete;
	CollidableDeregistrationCommand& operator=(const CollidableDeregistrationCommand) = delete;
	~CollidableDeregistrationCommand() = default;

	void execute();

private:
	Collidable* ptrCollidable;
};

#endif _CollidableDeregistrationCommand
