// ground plane with texture for demo game 

#ifndef _GroundPlane
#define _GroundPlane

#include "../GameObject.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "AzulCore.h"



class GroundPlane : public GameObject
{
public:

	GroundPlane() = delete;
	GroundPlane(float X = 0.0f, float Z = 0.0f);
	GroundPlane(const GroundPlane&) = delete;
	GroundPlane& operator =(const GroundPlane&) = delete;
	~GroundPlane();

	//void Update();

	void SceneEntry();
	void SceneExit();
	void Draw();

private:

	GraphicsObject_TextureFlat* pGObj_GroundPlane;

};

#endif _GroundPlane

