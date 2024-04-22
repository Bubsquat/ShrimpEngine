// command for up updating Draw Deregistration 

#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"
#include "RegistrationCommand.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* cmd)
	:ptrDrawable(cmd)
{}

void DrawDeregistrationCommand::execute()
{
	DrawableAttorney::Registration::SceneDeregistration(ptrDrawable);
}