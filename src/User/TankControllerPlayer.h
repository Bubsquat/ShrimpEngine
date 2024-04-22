// controller for tank that takes input from player

#ifndef _TankControllerPlayer
#define _TankControllerPlayer

#include "TankControllerBaseClass.h"

class Tank;
class Camera;

class TankControllerPlayer : public TankControllerBaseClass
{
public:

	TankControllerPlayer() = delete;
	TankControllerPlayer(Tank* pTank);
	TankControllerPlayer(const TankControllerPlayer&) = delete;
	TankControllerPlayer& operator=(const TankControllerPlayer&) = delete;
	~TankControllerPlayer();

	void Update();
	void SceneEntry();
	void SceneExit();

	void KeyHolding(AZUL_KEY k);
	void KeyPressed(AZUL_KEY k);

	void setTankToControl(Tank* _Tank);
	void ReportHit();

	void Alarm0();

private:

	Tank* pTank;
	Camera* playerCamera;

	int playerHealth;

	Matrix cameraPosMatrix;
	Matrix RotMatrix;
	Vect pCamPosOffset = { 0.0f, 50.0f, -200.0f};
	Vect pCamLookAt;
	Vect camPos;
	
	const float rotSpeed = 0.05f;
	const Vect TurretOffset = Vect(-10.0f, 20.0f, -10.0f);

	bool canTakeDamage;

};



#endif _TankControllerPlayer

