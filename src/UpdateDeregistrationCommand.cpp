// command for deregistering update registration 

#include "UpdateDeregistrationCommand.h"
#include "UpdateableAttorney.h"
#include "RegistrationCommand.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updateable* cmd)
	:ptrUpdateable(cmd)
{}

void UpdateDeregistrationCommand::execute()
{
	UpdateableAttorney::Registration::SceneDeregistration(ptrUpdateable);
}