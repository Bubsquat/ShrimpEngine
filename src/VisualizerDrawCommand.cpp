// visualizer draw command 

#include "VisualizerDrawCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraManager.h"

void VisualizerDrawCommand::Initialize(Matrix _world, Vect _col, GraphicsObject_WireframeConstantColor* _obj)
{
	this->world = _world;
	this->col = _col;
	this->pGO = _obj;
}

void VisualizerDrawCommand::Execute()
{

	pGO->SetWorld(world);
	pGO->SetColor(col);
	pGO->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}