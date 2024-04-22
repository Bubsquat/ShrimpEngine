// game skybox

#include "SkyBox.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include"../CameraManager.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"

SkyBox::SkyBox()
{

	//sky box sides as planes 

	sbTop = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbTopTex"));
	sbBottom = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbBottomTex"));
	sbBack = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbFrontTex"));
	sbFront = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbBackTex"));
	sbLeft = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbLeftTex"));
	sbRight = new GraphicsObject_TextureFlat(ModelManager::Get("planeModel"), ShaderManager::Get("texture"), TextureManager::Get("sbRightTex"));

	skyBoxCenter.set(0.0f, 0.0f, 0.0f, 1.0f);

	Scale = Matrix(SCALE, ScaleFactor, ScaleFactor, ScaleFactor);


	// set up the panels position 
	Matrix world;
	//font
	FrontRt = Matrix(ROT_X, MATH_PI / 2.0f) * Matrix(TRANS, 0.0f, ScaleFactor / 4.0f, -ScaleFactor / 2.0f + 1.0f);
	world = Scale * FrontRt;
	sbFront->SetWorld(world);
	//back
	BackRt = Matrix(ROT_Y, MATH_PI) * Matrix(ROT_X, -MATH_PI / 2.0f) * Matrix(TRANS, 0.0f, ScaleFactor / 4.0f, ScaleFactor / 2.0f - 1.0f);
	world = Scale * BackRt;
	sbBack->SetWorld(world);
	//left
	LeftRt = Matrix(ROT_X, MATH_PI / 2.0f) * Matrix(ROT_Y, -MATH_PI / 2) * Matrix(TRANS, ScaleFactor / 2.0f - 1.0f, ScaleFactor / 4.0f, 0.0f);
	world = Scale * LeftRt;
	sbLeft->SetWorld(world);
	//right
	RightRt = Matrix(ROT_X, MATH_PI / 2.0f) * Matrix(ROT_Y, MATH_PI / 2) * Matrix(TRANS, -ScaleFactor / 2.0f + 1.0f, ScaleFactor / 4.0f, 0.0f);
	world = Scale * RightRt;
	sbRight->SetWorld(world);
	//bottom
	BottomRt = Matrix(TRANS, 0.0f, -ScaleFactor / 4.0f + 1.0f, 0.0f);
	world = Scale * BottomRt;
	sbBottom->SetWorld(world);
	//top 
	TopRt = Matrix(ROT_X, MATH_PI) * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, 0.0f, ScaleFactor - ScaleFactor / 4.0f - 1.0f, 0.0f);
	world = Scale * TopRt;
	sbTop->SetWorld(world);


	SubmitEntry();
}


void SkyBox::SceneEntry()
{
	Drawable::SubmitDrawRegistration();

}

void SkyBox::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
}

SkyBox::~SkyBox()
{
	delete sbTop;
	delete sbBottom;
	delete sbLeft;
	delete sbRight;
	delete sbFront;
	delete sbBack;
}


void SkyBox::Draw()
{
	sbFront->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
	sbBack->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
	sbLeft->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
	sbRight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
	sbBottom->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
	sbTop->Render(SceneManager::GetCurrentScene()->GetCameraManager()->CameraManager::GetCurrentCamera());
}

void SkyBox::setPos(float x, float y, float z)
{
	skyBoxCenter.set(x, y, z, 1.0f);


	FrontRt *= Matrix(TRANS, skyBoxCenter);
	BackRt *= Matrix(TRANS, skyBoxCenter);
	LeftRt *= Matrix(TRANS, skyBoxCenter);
	RightRt *= Matrix(TRANS, skyBoxCenter);
	TopRt *= Matrix(TRANS, skyBoxCenter);
	BottomRt *= Matrix(TRANS, skyBoxCenter);

	Matrix world;

	world = Scale * FrontRt;
	sbFront->SetWorld(world);

	world = Scale * BackRt;
	sbBack->SetWorld(world);

	world = Scale * LeftRt;
	sbLeft->SetWorld(world);

	world = Scale * RightRt;
	sbRight->SetWorld(world);

	world = Scale * BottomRt;
	sbBottom->SetWorld(world);

	world = Scale * TopRt;
	sbTop->SetWorld(world);
}