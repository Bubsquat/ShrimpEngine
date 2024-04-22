// command for the right leg of the tank 

#ifndef _RightLegCommand
#define _RightLegCommand

#include "TankLegCommandBase.h"

class RightLegCommand : public TankLegCommandBase
{
public:

	RightLegCommand() = default;
	RightLegCommand(const RightLegCommand&) = delete;
	RightLegCommand& operator= (const RightLegCommand&) = delete;
	~RightLegCommand() = default;

	Vect GetOffset(LegPart p, int num);
	Vect GetRot(LegPart p, int num);

private:

	const Vect ThighPos[6] = {
		Vect(-39.0f, -9.0f, -6.0f), // resting position
		Vect(-39.0f, -3.0f, -3.0f), // first 
		Vect(-39.0f, -4.0f, -1.5f),
		Vect(-39.0f, -9.0f, -6.0f),
		Vect(-39.0f, -6.0f, -22.0f), // last frame
		Vect(-39.0f, -9.0f, -6.0f) // start the loop
	};

	const Vect ThighRot[6] = {
		Vect(-0.9f, 0.07f, 0.0f), // resting position
		Vect(-1.75f, 0.07f, 0.0f), // first frame
		Vect(-1.25f, 0.07f, 0.0f),
		Vect(-0.9f, 0.07f, 0.0f),
		Vect(1.0f, -0.07f, 0.0f), // last frame 
		Vect(-0.9f, 0.07f, 0.0f) // start the loop
	};

	const Vect FootPos[6] = {
		Vect(-39.0f, -13.0f, 7.0f), // resting position
		Vect(-39.0f, -2.0f, 14.0f), // first frame
		Vect(-39.0f, -13.0f, 19.0f),
		Vect(-39.0f, -13.0f, 5.0f),
		Vect(-39.0f, -12.0f, -30.0f), // last frame 
		Vect(-39.0f, -13.0f, 5.0f) // start the loop
	};

	const Vect FootRot[6] = {
		Vect(0.5f,0.0f,0.0f), // resting position
		Vect(-0.4f,0.0f,0.0f), // first frame
		Vect(-6.7f,0.0f,0.0f),
		Vect(0.8f,0.0f,0.0f),
		Vect(0.8f,0.0f,0.0f), // last frame
		Vect(0.8f,0.0f,0.0f) // start the loop
	};

};

#endif _RightLegCommand
