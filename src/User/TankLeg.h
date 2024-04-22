// tank leg that contains both a thigh and foot graphics object 

#ifndef _TankLeg
#define _TankLeg

#include "AzulCore.h"
#include "../GameObject.h"

class Tank;
class RightLegCommand;
class LeftLegCommand;
class TankLegCommandBase;

class TankLeg : public GameObject
{
public:

	enum Side
	{
		RIGHT,
		LEFT
	};

	TankLeg() = delete;
	TankLeg(Tank* pTank, Side side);
	TankLeg(const TankLeg&) = delete;
	TankLeg& operator =(const TankLeg&) = delete;
	~TankLeg();

	void Update();
	void Draw();
	void SceneEntry();
	void SceneExit();

	void Alarm0();

	void MoveForwards();
	void MoveBackwards();
	void OtherLegTurning();

private:

	Side legSide;

	GraphicsObject_TextureLight* pGObj_Thigh;
	GraphicsObject_TextureLight* pGObj_Foot;

	Matrix TScale;
	Matrix FScale;
	Matrix TRotTrans;
	Matrix FRotTrans;

	Tank* pMyTank;

	// animation stuff

	TankLegCommandBase* myCommand;
	RightLegCommand* rCommand;
	LeftLegCommand* lCommand;

	const int MaxFrames = 6;
	const float FrameRate = 0.14f;
	int ThighFrame;
	int FootFrame;

	bool movingForwards;
	bool movingBackwards;
	bool otherLegTurning;
	bool changeFrame;
};



#endif _TankLeg
