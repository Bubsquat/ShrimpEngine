// command for object scene deregistration 

#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "RegistrationCommand.h"
class GameObject;

class GameObjectExitCommand : public RegistrationCommand
{
public:

	GameObjectExitCommand() = delete;
	GameObjectExitCommand(GameObject* obj);
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand& operator=(const GameObjectExitCommand&) = delete;
	~GameObjectExitCommand() = default;

	void execute();

private:
	GameObject* ptrGameObject;
};

#endif _GameObjectEntryCommand
