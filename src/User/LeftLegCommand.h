// command for the Left leg of the tank 

#ifndef _LeftLegCommand
#define _LeftLegCommand

#include "TankLegCommandBase.h"

class LeftLegCommand : public TankLegCommandBase
{
public:

	LeftLegCommand() = default;
	LeftLegCommand(const LeftLegCommand&) = delete;
	LeftLegCommand& operator= (const LeftLegCommand&) = delete;
	~LeftLegCommand() = default;

	Vect GetOffset(LegPart p, int num);
	Vect GetRot(LegPart p, int num);

private:

	//const Vect ThighPos[6] = {
	//	Vect(39.0f, -9.0f, -6.0f), // resting position
	//	Vect(39.0f, -3.0f, -3.0f),
	//	Vect(39.0f, -4.0f, -1.5f),
	//	Vect(39.0f, -9.0f, -6.0f),
	//	Vect(39.0f, -6.0f, -22.0f),
	//	Vect(39.0f, -9.0f, -6.0f)
	//};

	const Vect ThighPos[6] = {
		Vect(39.0f, -9.0f, -6.0f),
		Vect(39.0f, -9.0f, -6.0f), // starting on 4th pos
		Vect(39.0f, -6.0f, -22.0f),
		Vect(39.0f, -9.0f, -6.0f),
		Vect(39.0f, -3.0f, -3.0f),
		Vect(39.0f, -4.0f, -1.5f)
	};

	//const Vect ThighRot[6] = {
	//	Vect(-0.9f, -0.07f, 0.0f), // resting position
	//	Vect(-1.75f, -0.07f, 0.0f),
	//	Vect(-1.25f, -0.07f, 0.0f),
	//	Vect(-0.9f, -0.07f, 0.0f),
	//	Vect(1.0f, 0.07f, 0.0f),
	//	Vect(-0.0f, -0.07f, 0.0f)
	//};

	const Vect ThighRot[6] = {
		Vect(-0.9f, -0.07f, 0.0f), // resting position
		Vect(-0.9f, -0.07f, 0.0f), // starting on 4th
		Vect(1.0f, 0.07f, 0.0f),
		Vect(-0.0f, -0.07f, 0.0f),
		Vect(-1.75f, -0.07f, 0.0f),
		Vect(-1.25f, -0.07f, 0.0f)
	};

	//const Vect FootPos[6] = {
	//	Vect(39.0f, -13.0f, 7.0f), // resting position
	//	Vect(39.0f, -2.0f, 14.0f),
	//	Vect(39.0f, -13.0f, 19.0f),
	//	Vect(39.0f, -13.0f, 5.0f),
	//	Vect(39.0f, -12.0f, -30.0f),
	//	Vect(39.0f, -13.0f, 5.0f)
	//};

	const Vect FootPos[6] = {
		Vect(39.0f, -13.0f, 7.0f), // resting position
		Vect(39.0f, -13.0f, 5.0f),
		Vect(39.0f, -12.0f, -30.0f),
		Vect(39.0f, -13.0f, 5.0f),
		Vect(39.0f, -2.0f, 14.0f),
		Vect(39.0f, -13.0f, 19.0f)
	};

	//const Vect FootRot[6] = {
	//	Vect(0.5f,0.0f,0.0f), // resting position
	//	Vect(-0.04f,0.0f,0.0f),
	//	Vect(-6.7f,0.0f,0.0f),
	//	Vect(0.8f,0.0f,0.0f),
	//	Vect(0.8f, 0.0f, 0.0f),
	//	Vect(0.8f,0.0f,0.0f)
	//};

	const Vect FootRot[6] = {
		Vect(0.5f,0.0f,0.0f), // resting position
		Vect(0.8f,0.0f,0.0f), // 4th
		Vect(0.8f, 0.0f, 0.0f),
		Vect(0.8f,0.0f,0.0f),
		Vect(-0.04f,0.0f,0.0f),
		Vect(-6.7f,0.0f,0.0f)
	};

};

#endif _LeftLegCommand