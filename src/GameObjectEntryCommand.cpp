// command for object scene registration 

#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* obj)
	: ptrGameObject(obj)
{}

void GameObjectEntryCommand::execute()
{
	GameObjectAttorney::SceneRegistration::ConnectToScene(ptrGameObject);
}