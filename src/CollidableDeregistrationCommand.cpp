// command for updating collision deregistration

#include "CollidableDeregistrationCommand.h"
#include "CollidableAttorney.h"

CollidableDeregistrationCommand::CollidableDeregistrationCommand(Collidable* obj)
	: ptrCollidable(obj)
{}


void CollidableDeregistrationCommand::execute()
{
	CollidableAttorney::Registration::SceneDeregistration(ptrCollidable);
}