// IKTank controller for player 

#include "IKTankControllerPlayer.h"
#include "IKTank.h"
#include "../Game.h"
#include "../SceneManager.h"
#include "../CameraManager.h"
#include "LevelManager.h"

#include "../Visualizer.h"

IKTankControllerPlayer::IKTankControllerPlayer()
{
	SceneEntry();
}

IKTankControllerPlayer::~IKTankControllerPlayer()
{
	delete playerCamera;
}

void IKTankControllerPlayer::SceneEntry()
{
	// registration
	Updateable::SubmitUpdateRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_R, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_F, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);

	canTakeDamage = true;
	playerHealth = 5;

	// set up player camera 

	playerCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	playerCamera->setViewport(0, 0, Game::GetWidth(), Game::GetHeight());
	playerCamera->setPerspective(35.0f, float(Game::GetWidth()) / float(Game::GetHeight()), 1.0f, 100000.0f);

	CamRotTrans = Matrix(IDENTITY);

	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(playerCamera);

}

void IKTankControllerPlayer::SceneExit()
{
	// deregistration
	Updateable::SubmitUpdateDeregistration();
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_R, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_F, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
}

void IKTankControllerPlayer::Update()
{
	updatePlayerCamera();
	LevelManager::UpdatePlayerLocation(pTank->GetTrans().get(ROW_3));
}

void IKTankControllerPlayer::KeyHolding(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_W:
		pTank->Forwards();
		break;
	case AZUL_KEY::KEY_S:
		pTank->Backwards();
		break;
	case AZUL_KEY::KEY_A:
		pTank->Left();
		break;
	case AZUL_KEY::KEY_D:
		pTank->Right();
		break;
	case AZUL_KEY::KEY_Q:
		pTank->TurnLeft();
		break;
	case AZUL_KEY::KEY_E:
		pTank->TurnRight();
		break;
	case AZUL_KEY::KEY_R:
		pTank->DeflectUp();
		break;
	case AZUL_KEY::KEY_F:
		pTank->DeflectDown();
		break;
	default:
		break;
	}
}

void IKTankControllerPlayer::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		pTank->Shoot();
		break;
	default:
		break;
	}
}

void IKTankControllerPlayer::updatePlayerCamera()
{

	//CamRotTrans = Matrix(TRANS, pCamPosOffset) * pTank->GetRot() * pTank->GetAlignMat() * pTank->GetTrans();
	//CamLookAt = (Matrix(TRANS, Vect(0, 100, 100.0f)) * pTank->GetRot() * pTank->GetAlignMat() * pTank->GetTrans()).get(ROW_3);

	CamRotTrans = Matrix(TRANS, pCamPosOffset) * pTank->GetTurretWorld();
	CamLookAt = (Matrix(TRANS, Vect(0, 150, 100.0f)) * pTank->GetTurretWorld()).get(ROW_3);

	playerCamera->setOrientAndPosition(Vect(0, 1, 0), CamLookAt, CamRotTrans.get(ROW_3));

	playerCamera->updateCamera();
}

void IKTankControllerPlayer::ReportHit()
{
	if (canTakeDamage)
	{
		// lower health 
		playerHealth--;

		LevelManager::UpdatePlayerHealth(playerHealth);
		canTakeDamage = false;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f); // imune to taking more damage for half a second 
	}
	
}

void IKTankControllerPlayer::Alarm0()
{
	canTakeDamage = true;
}