// game object 

#ifndef _GameObject
#define _GameObject

#include "Updateable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "Engine.h"
#include "RegistrationStateEnum.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject : public Updateable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;
public:

	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator = (const GameObject&) = delete;
	~GameObject();

	void SubmitEntry();
	void SubmitExit();

private:

	RegistrationState currentState;
	GameObjectEntryCommand* ptrEntryCmd;
	GameObjectExitCommand* ptrExitCmd;

	void ConnectToScene();
	void DisconnectFromScene();

	virtual void SceneEntry(); // user defined methods
	virtual void SceneExit();

};



#endif _GameObject
