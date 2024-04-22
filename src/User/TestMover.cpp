// point that moves around with keyboard imput for testing

#include "TestMover.h"
#include "../Visualizer.h"

TestMover::TestMover()
{
	SceneEntry();

	TransMat = Matrix(IDENTITY);

}

void TestMover::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyboardEvents::KEY_HOLDING);
}

void TestMover::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();

	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyboardEvents::KEY_HOLDING);
}

void TestMover::Update()
{

}

void TestMover::Draw()
{
	Visualizer::ShowMarker(TransMat.get(ROW_3), Colors::Purple, 1.5f); // just using visualizer to show test movers position
}

void TestMover::KeyHolding(AZUL_KEY k)
{

	if (k == AZUL_KEY::KEY_A)
	{
		TransMat = Matrix(TRANS, Vect(-speed, 0, 0)) * TransMat;
	}

	if (k == AZUL_KEY::KEY_D)
	{
		TransMat = Matrix(TRANS, Vect(speed, 0, 0)) * TransMat;
	}

	if (k == AZUL_KEY::KEY_W)
	{
		TransMat = Matrix(TRANS, Vect(0, 0, speed)) * TransMat;
	}

	if (k == AZUL_KEY::KEY_S)
	{
		TransMat = Matrix(TRANS, Vect(0, 0, -speed)) * TransMat;
	}

	if (k == AZUL_KEY::KEY_SPACE)
	{
		TransMat = Matrix(TRANS, Vect(0, speed, 0)) * TransMat;
	}

	if (k == AZUL_KEY::KEY_LEFT_SHIFT)
	{
		TransMat = Matrix(TRANS, Vect(0, -speed, 0)) * TransMat;
	}
}

Vect TestMover::MoverPosition()
{
	return TransMat.get(ROW_3);
}

void TestMover::SetPosition(Vect pos)
{
	TransMat = Matrix(TRANS, pos);
}