// demo game tank that uses the IK system to walk on terrain 

#ifndef _IKTank
#define _IKTank

#include "AzulCore.h"
#include "../GameObject.h"

class IKTankController;
class Linkage;
class BulletFactory;
class Bullet;

class IKTank : public GameObject
{
public:

	IKTank() = delete;
	IKTank(Vect startingPosition);
	IKTank(const IKTank&) = delete;
	IKTank& operator=(const IKTank&) = delete;
	~IKTank();

	void SceneEntry();
	void SceneExit();
	void Update();
	void Draw();

	void Alarm0();

	void Forwards();
	void Backwards();
	void Left();
	void Right();
	void TurnLeft();
	void TurnRight();
	void DeflectUp();
	void DeflectDown();
	void Shoot();

	void Collision(Bullet*);

	void SetController(IKTankController* controller);
	void SetBulletFactory(BulletFactory* bf);

	// accessors 
	Matrix GetRot();
	Matrix GetTrans();
	Matrix GetBodyWorld();
	Matrix GetTurretWorld();
	Matrix GetAlignMat();

private:

	IKTankController* myController;

	// tank body

	const float forwardsMoveSpeed = 20.0f;
	const float horizontalMoveSpeed = 13.0f;
	const float rotSpeed = 0.01f;

	float Yoffset = 75.0f;
	void SetBodyPos();

	GraphicsObject_TextureLight* pGO_TankBody;
	
	Matrix Rot;
	Matrix Trans;
	Matrix BodyRot;
	Matrix AlignMat;
	Matrix Scale;
	Matrix World;

	// tank turret 

	GraphicsObject_TextureLight* pGO_TankTurret;

	const Vect TurretOffset = Vect(0.0f, 77.0f, -36.0f);
	const float deflectSpeed = 0.015f;
	const float MinDeflect = -0.15f;
	const float MaxDeflect = .08f;

	float turretDeflect;
	Matrix turretAlign;
	Matrix turretWorld;

	// leg info 

	enum LEGS
	{
		RIGHT_FRONT,
		RIGHT_BACK,
		LEFT_FRONT,
		LEFT_BACK
	};

	GraphicsObject_TextureLight* pGO_TankLowerLeg;
	GraphicsObject_TextureLight* pGO_TankUpperLeg;

	Matrix LowerLegScale = Matrix(SCALE, Vect(1.0f,0.57f,1.0f));
	Matrix UpperLegScale = Matrix(SCALE, Vect(0.7f, 0.6f, 0.7f));

	const Vect RFLegOffset = Vect(85.0f, -5.0f, 50.0f);
	const Vect RBLegOffset = Vect(85.0f, -5.0f, -115.0f);
	const Vect LFLegOffset = Vect(-85.0f, -5.0f, 50.0f);
	const Vect LBLegOffset = Vect(-85.0f, -5.0f, -115.0f);
	
	const float LegTravel = 0.03f;
	const float MaxAngle = (MATH_PI / 2) -  2 * (MATH_PI / 8);

	const float TargetYOffset = 45.0f;
	const float LegRaiseSpeed = 2.2f;

	Vect RFLegPos;
	Vect RBLegPos;
	Vect LFLegPos;
	Vect LBLegPos;

	Linkage* RFLinkage;
	Linkage* RBLinkage;
	Linkage* LFLinkage;
	Linkage* LBLinkage;

	Vect RFTargetPos;
	Vect RBTargetPos;
	Vect LFTargetPos;
	Vect LBTargetPos;

	Vect RFTargetVect;
	Vect RBTargetVect;
	Vect LFTargetVect;
	Vect LBTargetVect;

	float RFAngle;
	float RBAngle;
	float LFAngle;
	float LBAngle;

	int RFDir;
	int RBDir;
	int LFDir;
	int LBDir;

	float RFY;
	float RBY;
	float LFY;
	float LBY;

	void advanceWalkVector(LEGS leg);

	// fireing 

	bool canFire; 
	const Vect bulletOffset = Vect(0.0f, 60.0f, 215.0f);
	BulletFactory* myBulletFactory;

};

#endif _IKTank

