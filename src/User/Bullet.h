// bullet that travels forwards and has a lifetime 

#ifndef _Bullet
#define _Bullet

#include "AzulCore.h"
#include "../GameObject.h"

class BulletFactory;
class Cottage;
class Tank;
class IKTank;

class Bullet : public GameObject
{
public:

	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator =(const Bullet&) = delete;
	~Bullet();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void Alarm0();

	void Initialize(Matrix RotTrans);
	void SetFactory(BulletFactory* factory);

	void Collision(Bullet*);
	void Collision(Cottage*);
	void Collision(Tank*);
	void Collision(IKTank*);
	//void CollisionTerrain();

private:

	BulletFactory* myFactory;
	GraphicsObject_WireframeConstantColor* pGObj_Bullet;
	Matrix RotTrans;
	Matrix Scale; 
	float speed;
	float lifetime;

};


#endif _Bullet
