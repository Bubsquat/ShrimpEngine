//command to run when scene needs to be changed

#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

void SceneChangeCommand::SetNewScene(Scene* _newScene)
{
	this->newScene = _newScene;
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::SceneChange::ChangeScene(newScene);
}