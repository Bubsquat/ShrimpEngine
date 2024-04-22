// ground plane with texture for demo game 

#include "GroundPlane.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include"../CameraManager.h"

GroundPlane::GroundPlane(float _X, float _Z)
{
	pGObj_GroundPlane = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("asphaultTex"));

	Matrix world;
	world = Matrix(SCALE, 1500, 1500, 1500) * Matrix(TRANS, _X, 0.0f, _Z);
	pGObj_GroundPlane->SetWorld(world);

	SubmitEntry();

}

void GroundPlane::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
}

void GroundPlane::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
}


GroundPlane::~GroundPlane()
{
	delete pGObj_GroundPlane;
}

void GroundPlane::Draw()
{
	
	pGObj_GroundPlane->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
}