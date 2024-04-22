// attribute that allows a game object to be updatable 

#ifndef _Updateable
#define _Updateable

#include "UpdateableManager.h"


enum class RegistrationState;
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updateable
{
	friend class UpdateableAttorney;
	
public:

	Updateable();
	Updateable(const Updateable&) = delete;
	Updateable& operator =(const Updateable&) = delete;
	~Updateable();

	void SubmitUpdateRegistration();
	void SubmitUpdateDeregistration();

private:
	
	RegistrationState currentState; 
	UpdateableManager::UpdateListRef pMyDeleteRef;
	UpdateRegistrationCommand* pRegCmd;
	UpdateDeregistrationCommand* pDeregCmd;

	UpdateableManager::UpdateListRef GetListRef();
	void SetListRef(UpdateableManager::UpdateListRef ref);
	void SetRegistrationState(RegistrationState);

	void SceneRegistration();
	void SceneDeregistration();

	virtual void Update();
};



#endif _Updateable
