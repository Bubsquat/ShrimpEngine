// plane from demo

#include"Plane.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include"../CameraManager.h"

Plane::Plane()
{

	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("planeTex"));

	Matrix world;
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Plane->SetWorld(world);

	Drawable::SubmitDrawRegistration();

	//collision testing 
	SetCollidableGroup<Plane>();
}

void Plane::Update()
{

}

void Plane::Draw()
{
	pGObj_Plane->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
}

Plane::~Plane()
{
	delete pGObj_Plane;
}