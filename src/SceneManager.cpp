// singleton scene manager 

#include "SceneManager.h"
#include <assert.h>
#include "Scene.h"
#include "SceneChangeCommandBase.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include "NullScene.h"

SceneManager* SceneManager::ptrInstance = nullptr; 

SceneManager::SceneManager()
{
	doNothingCommand = new SceneChangeNullCommand();
	changeCommand = new SceneChangeCommand();
	nullScene = new NullScene();

	executeCmd = doNothingCommand; // dont change scene by default
	currentScene = nullScene; // default scene is null scene 
}

SceneManager::~SceneManager()
{
	delete changeCommand;
	delete doNothingCommand;
	// we aren't deleting nullScene because the scene change deletes the previous scene, so having a scene deletes null scene 
}

void SceneManager::privUpdate()
{
	executeCmd->Execute(); // execute current scene change cmd

	currentScene->Update();
}

void SceneManager::privDraw()
{
	currentScene->Draw();
}

Scene* SceneManager::privGetCurrentScene()
{
	return currentScene;
}

void SceneManager::privSetStartScene(Scene* newScene)
{
	//startScene = newScene;
	//currentScene = startScene;

	SetNextScene(newScene);
}

void SceneManager::privDelete()
{

	//startScene->SceneEnd();
	//delete startScene;
	currentScene->SceneEnd();
	delete currentScene; // might not need this delete here

	delete ptrInstance; 
	ptrInstance = nullptr;
}

void SceneManager::privChangeScene(Scene* _newScene)
{

	currentScene->SceneEnd();
	
	delete currentScene;

	currentScene = _newScene;
	currentScene->Initialize();

	executeCmd = doNothingCommand; // set change command back to doing nothing 
}

void SceneManager::SetNextScene(Scene* _newScene)
{
	assert(_newScene != currentScene); // dont allow double changing ? 
	assert(currentScene);

	changeCommand->SetNewScene(_newScene);
	executeCmd = changeCommand;
}