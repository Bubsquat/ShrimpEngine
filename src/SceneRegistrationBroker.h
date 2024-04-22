// Scene registratiom broker 

#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <queue>

class RegistrationCommand;

class SceneRegistrationBroker
{

public:

	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator =(const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker();

	void addCommands(RegistrationCommand* cmd);
	void executeCommands();

private:

	using RegistrationCommandList = std::queue<RegistrationCommand*>;
	RegistrationCommandList commandList;

};




#endif _SceneRegistrationBroker
