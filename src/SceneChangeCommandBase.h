// base class for scene change strategy pattern

#ifndef _SceneChangeCommandBase
#define _SceneChangeCommandBase

class Scene;

class SceneChangeCommandBase
{
public:

	SceneChangeCommandBase() = default;
	SceneChangeCommandBase(const SceneChangeCommandBase&) = delete;
	SceneChangeCommandBase& operator= (const SceneChangeCommandBase&) = delete;
	virtual ~SceneChangeCommandBase() = default;

	virtual void Execute() = 0;
	virtual void SetNewScene(Scene* ) = 0;

private:

};



#endif _SceneChangeCommandBase
