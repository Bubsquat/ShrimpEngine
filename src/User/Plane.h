// plane from demo

#ifndef _Plane
#define _Plane

#include "../GameObject.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "AzulCore.h"



class Plane : public GameObject
{
public:

	Plane();
	Plane(const Plane&) = delete;
	Plane& operator =(const Plane&) = delete;
	~Plane();

	void Update();
	void Draw();

private:

	GraphicsObject_TextureFlat* pGObj_Plane;

};

#endif _Plane

