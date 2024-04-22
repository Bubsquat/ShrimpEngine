// demo frigate 

#ifndef _Frigate
#define _Frigate

#include "../GameObject.h"
#include "AzulCore.h"

class Frigate : public GameObject
{
public:

	Frigate();
	Frigate(const Frigate&) = delete;
	Frigate& operator =(const Frigate&) = delete;
	~Frigate();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void KeyHolding(AZUL_KEY k);
	void KeyPressed(AZUL_KEY k);
	void KeyReleased(AZUL_KEY k);

	void Alarm0();
	void Alarm1();

	void Collision(Frigate*);

private:

	GraphicsObject_TextureLight* pGObj_SpaceFrigateLight;
	//GraphicsObject_WireframeConstantColor* pGObj_SpaceshipBSphere;

	Matrix ShipScale;
	Matrix ShipRotTrans;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	bool BsphereToggle = false;

	int testCounter;

};


#endif _Frigate
