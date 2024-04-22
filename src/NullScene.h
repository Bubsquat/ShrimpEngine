// null scene for internal use 

#ifndef _NullScene
#define _NullScene

#include "Scene.h"

class NullScene : public Scene
{
public:
	~NullScene() = default;
	virtual void Initialize() {};
	virtual void SceneEnd() {};
};


#endif _NullScene
