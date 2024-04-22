// attribute that allows a game object to be updated 

#ifndef _Drawable
#define _Drawable

#include "DrawableManager.h"

enum class RegistrationState; 
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{

	friend class DrawableAttorney;

public:

	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator= (const Drawable&) = delete;
	~Drawable(); 

	void SubmitDrawRegistration();
	void SubmitDrawDeregistration();

private:

	RegistrationState currentState;
	DrawableManager::DrawListRef pMyDeleteRef;
	DrawRegistrationCommand* pRegCmd;
	DrawDeregistrationCommand* pDeregCmd;

	void SceneRegistration();
	void SceneDeregistration();
	DrawableManager::DrawListRef GetListRef();
	void SetListRef(DrawableManager::DrawListRef ref);

	void SetRegistrationState(RegistrationState);

	virtual void Draw();
	virtual void Draw2D();

};



#endif _Drawable
