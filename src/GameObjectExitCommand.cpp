// command for object scene deregistration 

#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* obj)
	: ptrGameObject(obj)
{}

void GameObjectExitCommand::execute()
{
	GameObjectAttorney::SceneRegistration::DisconnectFromScene(ptrGameObject);
}