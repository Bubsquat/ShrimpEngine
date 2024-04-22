// no op command to run when scene change is not needed 

#ifndef _SceneChangeNullCommand
#define _SceneChangeNullCommand

#include "SceneChangeCommandBase.h"
class Scene;

class SceneChangeNullCommand : public SceneChangeCommandBase
{
	virtual void Execute() {};
	virtual void SetNewScene(Scene* ) {};
};

#endif _SceneChangeNullCommand
