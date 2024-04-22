// attorney for the scene manager

#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"
class Scene;

class SceneManagerAttorney
{

public:

	class GameLoop
	{
		friend class Game;

	private:

		static void Update() { SceneManager::Update(); };
		static void Draw() { SceneManager::Draw(); };
		static void Terminate() { SceneManager::Terminate(); };
	};

public:

	class SceneChange
	{
		friend class SceneChangeCommand;

	private:
		static void ChangeScene(Scene* newScene) { SceneManager::Instance().privChangeScene(newScene); };
	};

};


#endif _SceneManagerAttorney
