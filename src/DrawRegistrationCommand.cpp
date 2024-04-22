// command for updating Draw registration 

#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"
#include "RegistrationCommand.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* cmd)
	:ptrDrawable(cmd)
{}

void DrawRegistrationCommand::execute()
{
	DrawableAttorney::Registration::SceneRegistration(ptrDrawable);
}