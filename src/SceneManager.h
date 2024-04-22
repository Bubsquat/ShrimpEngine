// singleton scene manager 

#ifndef _SceneManager
#define _SceneManager

#include "SceneChangeCommandBase.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include "NullScene.h"

class Scene;

class SceneManager
{
	friend class SceneManagerAttorney;
private:

	SceneManager(); // set up defaults here? 
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator= (const SceneManager&) = delete; 
	~SceneManager();

	static SceneManager* ptrInstance;

	static SceneManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new SceneManager();
		}
		return *ptrInstance;
	}


	Scene* currentScene; 

	// functions 
	void privUpdate();
	void privDraw();
	Scene* privGetCurrentScene();
	void privSetStartScene(Scene* newScene);
	void privDelete();

	void SetNextScene(Scene* newScene);
	void privChangeScene(Scene* newScene);

	SceneChangeCommand* changeCommand;
	SceneChangeNullCommand* doNothingCommand;
	SceneChangeCommandBase* executeCmd;
	NullScene* nullScene;
	
	static void Draw() { Instance().privDraw(); }
	static void Terminate() { Instance().privDelete(); }
	static void Update() { Instance().privUpdate(); }

public:

	// services
	static Scene* GetCurrentScene() { return Instance().privGetCurrentScene(); }
	static void SetStartScene(Scene* newScene) { Instance().privSetStartScene(newScene); }
	static void SubmitSceneChange(Scene* newScene) { Instance().SetNextScene(newScene); };

};


#endif _SceneManager
