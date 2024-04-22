// Scene registratiom broker 

#include "SceneRegistrationBroker.h"
#include "RegistrationCommand.h"

void SceneRegistrationBroker::addCommands(RegistrationCommand* cmd)
{
	commandList.push(cmd);
}

void SceneRegistrationBroker::executeCommands()
{

	while (!commandList.empty())
	{
		commandList.front()->execute();
		commandList.pop();
	}

}

SceneRegistrationBroker::~SceneRegistrationBroker()
{
	while (!commandList.empty())
	{
		commandList.pop();
	}
}