// controller for tank that takes input from player

#include "TankControllerPlayer.h"
#include "Tank.h"
#include "Camera.h"
#include "../CameraManager.h"
#include "../SceneManager.h"
#include "../Game.h"
#include "LevelManager.h"
#include "TankTurret.h"

TankControllerPlayer::TankControllerPlayer(Tank* _pTank)
{
	pTank = _pTank;

	SceneEntry();
}

TankControllerPlayer::~TankControllerPlayer()
{
	delete playerCamera;
}

void TankControllerPlayer::SceneEntry()
{

	Updateable::SubmitUpdateRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);

	// create camera for tank 

	playerCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	playerCamera->setViewport(0, 0, Game::GetWidth(), Game::GetHeight());
	playerCamera->setPerspective(35.0f, float(Game::GetWidth()) / float(Game::GetHeight()), 1.0f, 100000.0f);

	//cameraPosMatrix = Matrix(TRANS, pCamPosOffset) * Matrix(TRANS, -30, 40, -100);
	//cameraRotMatrix = Matrix(ROT_Y, 0.0f);

	RotMatrix = Matrix(ROT_Y, 0.0f);

	pCamLookAt.set(0.0f, 0.0f, 5000.0f, 0.0f);

	cameraPosMatrix = Matrix(TRANS, pCamPosOffset) * pTank->GetTurret()->GetRTMatrix();

	playerCamera->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), pCamLookAt, cameraPosMatrix.get(MatrixRowType::ROW_3));
	
	playerCamera->updateCamera();

	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(playerCamera);

	// set player health
	playerHealth = 5;
	LevelManager::UpdatePlayerHealth(playerHealth);
	canTakeDamage = true;
}

void TankControllerPlayer::SceneExit()
{

	Updateable::SubmitUpdateDeregistration();
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);

}

void TankControllerPlayer::Update()
{

	pTank->GetTurret()->Rot(RotMatrix);

	cameraPosMatrix = Matrix(TRANS, pCamPosOffset) * pTank->GetTurret()->GetRTMatrix();

	Vect LookAt = pCamLookAt * RotMatrix; // rotation gets off sync, look into this 

	playerCamera->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), LookAt, cameraPosMatrix.get(MatrixRowType::ROW_3));

	//DebugMsg::out("X: %f Y: %f Z: %F\n", LookAt.X(), LookAt.Y(), LookAt.Z());

	playerCamera->updateCamera();

}

void TankControllerPlayer::setTankToControl(Tank* _pTank)
{
	pTank = _pTank;
	pTank->SetController(this);
}

void TankControllerPlayer::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE) pTank->Shoot();
}

void TankControllerPlayer::KeyHolding(AZUL_KEY k)
{
	// move tank
	if (k == AZUL_KEY::KEY_W)
	{
		pTank->Forwards();
		LevelManager::UpdatePlayerLocation(pTank->GetRTMatrix().get(MatrixRowType::ROW_3));
	}
	if (k == AZUL_KEY::KEY_S) 
	{
		pTank->Backwards();
		LevelManager::UpdatePlayerLocation(pTank->GetRTMatrix().get(MatrixRowType::ROW_3));
	}

	if (k == AZUL_KEY::KEY_Q) pTank->Left();
	if (k == AZUL_KEY::KEY_E) pTank->Right();

	//rotate turret and camera 
	if (k == AZUL_KEY::KEY_A) RotMatrix *= Matrix(ROT_Y, rotSpeed);
	if (k == AZUL_KEY::KEY_D) RotMatrix *= Matrix(ROT_Y, -rotSpeed);

}

void TankControllerPlayer::ReportHit()
{

	if (canTakeDamage)
	{
		// shake camera ? (not enough time)
		  
		// lower health 
		playerHealth--;

		LevelManager::UpdatePlayerHealth(playerHealth);
		canTakeDamage = false;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 0.5f); // imune to taking more damage for half a second 
	}
}

void TankControllerPlayer::Alarm0()
{
	canTakeDamage = true;
}