// turret for tank

#ifndef _TankTurret
#define _TankTurret

#include "../GameObject.h"
#include "AzulCore.h"

class Tank;
class BulletFactory;

class TankTurret : public GameObject
{
public:
	TankTurret() = delete;
	TankTurret(Tank* pTank, BulletFactory* pBulletFactory);
	TankTurret(const TankTurret&) = delete;
	TankTurret& operator=(const TankTurret&) = delete;
	~TankTurret();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void Alarm0();

	void Shoot();
	void Rot(Matrix rot);

	Matrix GetRTMatrix();

private:

	GraphicsObject_TextureLight* pGObj_TurretLight;
	Matrix Scale;
	Matrix RotTrans;
	Vect TurretOffset;
	Matrix CurrentRot;
	const Matrix TurretDeflection = Matrix(ROT_X, 0.02f);

	Tank* pMyTank;

	BulletFactory* bulletFactory;
	bool canShoot;

	Matrix TurretPosition;
	Vect BulletOffset = { 0.0f, -0.55f, 56.0f};


};


#endif _TankTurret
