// manager for game cameras 

#include "CameraManager.h"
#include "AzulCore.h"
#include "Game.h"

CameraManager::CameraManager()
{
	// create default orthographic 2D camera 

	ortho2DCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	ortho2DCamera->setViewport(0, 0, Game::GetWidth(), Game::GetHeight());
	ortho2DCamera->setOrthographic(-0.5f * Game::GetWidth(), 0.5f * Game::GetWidth(), -0.5f * Game::GetHeight(), 0.5f * Game::GetHeight(), 1.0f, 1000.0f);

	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	ortho2DCamera->setOrientAndPosition(up2DCam, pos2DCam, lookAt2DCam);

	// create god cam here 
	defaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D); 
	defaultCamera->setViewport(0, 0, Game::GetWidth(), Game::GetHeight());
	defaultCamera->setPerspective(35.0f, float(Game::GetWidth()) / float(Game::GetHeight()), 1.0f, 100000.0f);

	// set up god cam 
	defaultCamStartPos.up3DCam = { 0.0f, 1.0f, 0.0f };
	defaultCamStartPos.pos3DCam = { 50.0f, 50.0f, 150.0f };
	defaultCamStartPos.lookAt3DCam = { 0.0f, 0.0f, 0.0f };
	defaultCamSpeed = 14;
	defaultCamRotSpeed = 0.04f;

	defaultCamCurrentPos = defaultCamStartPos;
	defaultCamera->setOrientAndPosition(defaultCamCurrentPos.up3DCam, defaultCamCurrentPos.lookAt3DCam, defaultCamCurrentPos.pos3DCam);
	defaultCamera->updateCamera();

	currentCamera = defaultCamera;
}

CameraManager::~CameraManager()
{
	// delete god cam here 
	delete defaultCamera; 
	delete ortho2DCamera;
}

void CameraManager::UpdateDefaultCam()
{

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_RIGHT_CONTROL)) // reset default cam pos 
	{
		defaultCamCurrentPos.up3DCam = defaultCamStartPos.up3DCam;
		defaultCamCurrentPos.lookAt3DCam = defaultCamStartPos.lookAt3DCam;
		defaultCamCurrentPos.pos3DCam = defaultCamStartPos.pos3DCam;
	}
	else
	{
		Vect CamPos = defaultCamCurrentPos.pos3DCam;
		Vect CamDir(0, 0, 1);
		Vect CamUp(0, 1, 0);
		Matrix CamRot(ROT_ORIENT, defaultCamCurrentPos.lookAt3DCam - defaultCamCurrentPos.pos3DCam, CamUp);

		// update camera position 
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
		{
			CamPos += Vect(0, 0, 1) * CamRot * defaultCamSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
		{
			CamPos += Vect(0, 0, 1) * CamRot * -defaultCamSpeed;
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
		{
			CamPos += Vect(1, 0, 0) * CamRot * defaultCamSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
		{
			CamPos += Vect(1, 0, 0) * CamRot * -defaultCamSpeed;
		}

		// update cam target
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
		{
			CamRot *= Matrix(ROT_Y, defaultCamRotSpeed);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
		{
			CamRot *= Matrix(ROT_Y, -defaultCamRotSpeed);
		}

		if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
		{
			CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -defaultCamRotSpeed);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
		{
			CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, defaultCamRotSpeed);
		}

		defaultCamCurrentPos.up3DCam = CamUp * CamRot;
		defaultCamCurrentPos.lookAt3DCam = CamPos + CamDir * CamRot;
		defaultCamCurrentPos.pos3DCam = CamPos;
	}

	defaultCamera->setOrientAndPosition(defaultCamCurrentPos.up3DCam, defaultCamCurrentPos.lookAt3DCam, defaultCamCurrentPos.pos3DCam);
}

void CameraManager::UpdateCurrentCamera()
{
	currentCamera->updateCamera();
}

void CameraManager::Update2DCamera()
{
	ortho2DCamera->updateCamera();
}

void CameraManager::SetCurrentCamera(Camera* newCamera)
{

	this->currentCamera = newCamera;

}

Camera* CameraManager::GetCurrentCamera()
{
	return this->currentCamera;
}

Camera* CameraManager::Get2DCamera()
{
	return this->ortho2DCamera;
}

void CameraManager::SwitchToDefaultCamera()
{
	this->currentCamera = defaultCamera;
}