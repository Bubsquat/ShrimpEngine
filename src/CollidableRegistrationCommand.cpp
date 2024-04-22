// command for updating collision registration

#include "CollidableRegistrationCommand.h"
#include "CollidableAttorney.h"

CollidableRegistrationCommand::CollidableRegistrationCommand(Collidable* obj)
	: ptrCollidable(obj)
{}

void CollidableRegistrationCommand::execute()
{
	CollidableAttorney::Registration::SceneRegistration(ptrCollidable);
}