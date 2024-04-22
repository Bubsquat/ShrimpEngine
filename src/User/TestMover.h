// point that moves around with keyboard imput for testing

#ifndef _TestMover
#define _TestMover

#include "AzulCore.h"
#include "../GameObject.h"

class TestMover : public GameObject
{
public:

	TestMover();
	TestMover(const TestMover&) = delete;
	TestMover& operator=(const TestMover&) = delete;
	~TestMover() = default;

	void SceneEntry();
	void SceneExit();
	void Update();
	void Draw();

	void KeyHolding(AZUL_KEY k);

	Vect MoverPosition();
	void SetPosition(Vect pos);

private:

	const float speed = 1.0f;
	Matrix TransMat;

};


#endif _TestMover
