// frigate that shoots and is controlled by the player 

#ifndef _ShootingFrigate
#define _ShootingFrigate

#include "../GameObject.h"
#include "AzulCore.h"
#include "BulletFactory.h"

class Cottage;

class ShootingFrigate : public GameObject
{
public:

	ShootingFrigate();
	ShootingFrigate(const ShootingFrigate&) = delete;
	ShootingFrigate& operator =(const ShootingFrigate&) = delete;
	~ShootingFrigate();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void KeyHolding(AZUL_KEY k);
	void KeyPressed(AZUL_KEY k);

	void Collision(Cottage*);
	void Collision(ShootingFrigate*);
	void CollisionTerrain();

	// for testing purposes
	Vect getPos();

private:

	GraphicsObject_TextureLight* pGObj_SpaceFrigateLight;

	Matrix ShipScale;
	Matrix ShipRotTrans;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;

	BulletFactory myBulletFactory;

	//collision testing 
	bool collide;

};






#endif _ShootingFrigate
