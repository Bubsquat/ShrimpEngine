// command for updating update registration 

#include "UpdateRegistrationCommand.h"
#include "UpdateableAttorney.h"
//#include "Updateable.h"
#include "RegistrationCommand.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updateable* cmd)
	:ptrUpdateable(cmd)
{}

void UpdateRegistrationCommand::execute()
{
	UpdateableAttorney::Registration::SceneRegistration(ptrUpdateable);
}