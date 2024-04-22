// axis from demo

#include"Axis.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../CameraManager.h"

Axis::Axis()
{

	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("axisModel"), ShaderManager::Get("colorNoTexture"));

	Matrix world;
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);

	Drawable::SubmitDrawRegistration();
}

void Axis::Update()
{

}

void Axis::Draw()
{
	pGObj_Axis->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

Axis::~Axis()
{
	delete pGObj_Axis;
}