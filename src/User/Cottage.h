// static cottage

#ifndef _Cottage
#define _Cottage

//#include "AzulCore.h"
#include "../GameObject.h"

class ShootingFrigate;
class Bullet;

class Cottage : public GameObject
{
public:

	Cottage();
	Cottage(const Cottage&) = delete;
	Cottage& operator= (const Cottage&) = delete;
	~Cottage();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void Collision(ShootingFrigate*);
	void Collision(Bullet*);

	void SetPosition(Vect pos);

private:

	GraphicsObject_TextureLight* pGObj_CottageLight;
	Matrix Scale;
	Matrix RotTrans;
	bool collide;

};


#endif !_Cottage
