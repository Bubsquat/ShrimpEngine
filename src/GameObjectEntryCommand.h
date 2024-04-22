// command for object scene registration 

#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "RegistrationCommand.h"
class GameObject;

class GameObjectEntryCommand : public RegistrationCommand
{
public:

	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(GameObject* obj);
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand& operator=(const GameObjectEntryCommand&) = delete;
	~GameObjectEntryCommand() = default;

	void execute();

private:
	GameObject* ptrGameObject;
};

#endif _GameObjectEntryCommand
