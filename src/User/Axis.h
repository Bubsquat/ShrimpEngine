// Axis from demo

#ifndef _Axis
#define _Axis

#include "../GameObject.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "AzulCore.h"



class Axis : public GameObject
{
public:

	Axis();
	Axis(const Axis&) = delete;
	Axis& operator =(const Axis&) = delete;
	~Axis();

	void Update();
	void Draw();

private:

	GraphicsObject_ColorNoTexture* pGObj_Axis;

};

#endif _Axis
