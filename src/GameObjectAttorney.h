// attorney for game object scene registration and deregistration

#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

class GameObjectAttorney
{
public:
	class SceneRegistration // seperating this out incase we need other functions for this attorney
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;
	private:
		static void ConnectToScene(GameObject* obj) { obj->ConnectToScene(); };
		static void DisconnectFromScene(GameObject* obj) { obj->DisconnectFromScene(); };
	};

};




#endif _GameObjectAttorney
