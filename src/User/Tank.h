// tank 

#ifndef _Tank
#define _Tank

#include "AzulCore.h"
#include "../GameObject.h"

class BulletFactory;
class TankTurret;
class TankLeg;
class Bullet;
class TankControllerBaseClass;

class Tank : public GameObject
{
public: 

	Tank(BulletFactory* pBulletFactory, float Xpos, float Zpos);
	Tank(const Tank&) = delete;
	Tank& operator=(const Tank&) = delete;
	~Tank();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	//void Alarm0();

	void Shoot();
	void Forwards();
	void Backwards();
	void Left();
	void Right();

	void Collision(Bullet*);
	//void Collision(Tank*);

	Matrix GetRTMatrix();
	Vect GetRotation();
	void RotateTurret(Matrix Rot);
	TankTurret* GetTurret();

	void SetController(TankControllerBaseClass* pC);

private:

	GraphicsObject_TextureLight* pGObj_TankLight;
	Matrix Scale;
	Matrix RotTrans;
	Vect XYZRot;

	float moveSpeed = 2.0f;
	float rotSpeed = 0.05f;
	float TankLean = 0.15f;
	BulletFactory* pBulletFactory; 
	TankTurret* myTurret;
	TankLeg* myRightLeg;
	TankLeg* myLeftLeg;

	enum LeanStatus
	{
		FORWARDS,
		BACKWARDS,
		NONE
	};

	LeanStatus curLean;

	TankControllerBaseClass* myController;

};

#endif _Tank
