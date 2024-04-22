//command to run when scene needs to be changed

#ifndef _SceneChangeCommand
#define _SceneChangeCommand

#include "SceneChangeCommandBase.h"
class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand() = default;
	virtual void Execute();
	virtual void SetNewScene(Scene* _newScene);
private:
	Scene* newScene;
};

#endif _SceneChangeCommand
