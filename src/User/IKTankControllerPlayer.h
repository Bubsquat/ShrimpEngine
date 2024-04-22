// IKTank controller for player 

#ifndef _IKTankControllerPlayer
#define _IKTankControllerPlayer

#include "IKTankController.h"

class IKTankControllerPlayer : public IKTankController
{
public:

	IKTankControllerPlayer(); 
	IKTankControllerPlayer(const IKTankControllerPlayer&) = delete;
	IKTankControllerPlayer& operator=(const IKTankControllerPlayer&) = delete;
	~IKTankControllerPlayer();

	void SceneEntry();
	void SceneExit();
	void Update();

	void KeyHolding(AZUL_KEY k);
	void KeyPressed(AZUL_KEY k);

	void Alarm0();

	void ReportHit();

private:

	Camera* playerCamera;
	void updatePlayerCamera();

	Vect CamLookAt;
	Matrix CamRotTrans;
	Vect pCamPosOffset = { 0.0f, 400.0f, -1200.0f };

	bool canTakeDamage;
	int playerHealth;
};


#endif _IKTankControllerPlayer
