// tank leg that contains both a thigh and foot graphics object 

#include "TankLeg.h"
#include "Tank.h"
#include <assert.h>
#include "../ModelManager.h"
#include "../ShaderManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../CameraManager.h"
#include "TankLegCommandBase.h"
#include "RightLegCommand.h"
#include "LeftLegCommand.h"


TankLeg::TankLeg(Tank* _pTank, Side _side)
{
	pMyTank = _pTank;
	legSide = _side;

	movingForwards = false;
	movingBackwards = false;
	changeFrame = false;
	ThighFrame = 0;
	FootFrame = 0;
	otherLegTurning = false;

	rCommand = new RightLegCommand();
	lCommand = new LeftLegCommand();

	// set up graphics objects 
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_Thigh = new GraphicsObject_TextureLight(ModelManager::Get("tankThighModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);
	pGObj_Foot = new GraphicsObject_TextureLight(ModelManager::Get("tankFootModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);
	
	TScale.set(SCALE, 0.08f, 0.08f, 0.08f);
	FScale.set(SCALE, 0.08f, 0.08f, 0.08f);

	Matrix thighWorld;
	Matrix footWorld;

	switch (legSide) // leg set up depends on side of tank 
	{
	case Side::LEFT:

		myCommand = lCommand;
		break;

	case Side::RIGHT:

		myCommand = rCommand;
		break;

	default:
		assert("Error: Tank leg side not set.");
		break;
	}


	TRotTrans = Matrix(ROT_X, 0) * Matrix(TRANS, myCommand->GetOffset(TankLegCommandBase::LegPart::Thigh, 1));
	FRotTrans = Matrix(ROT_X, 0) * Matrix(TRANS, myCommand->GetOffset(TankLegCommandBase::LegPart::Foot, 1));

	thighWorld = TScale * TRotTrans;
	footWorld = FScale * FRotTrans;

	pGObj_Thigh->SetWorld(thighWorld);
	pGObj_Foot->SetWorld(footWorld);

	// enter scene
	SubmitEntry();
}

TankLeg::~TankLeg()
{
	delete rCommand;
	delete lCommand;
	delete pGObj_Thigh;
	delete pGObj_Foot;
}

void TankLeg::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();

	// start animation loop
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, FrameRate);
}

void TankLeg::SceneExit()
{
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
}

void TankLeg::Update()
{

	// check what animations should be running 

	// this if tree is rough, change with a fsm in later iteration of the actual animation system? 
	if (changeFrame)
	{
		if (!movingBackwards && !movingForwards) // set to resting frame is we are not moving 
		{
			ThighFrame = 0;
			FootFrame = 0;
		}
		else if (movingForwards)
		{

			ThighFrame++;
			FootFrame++;
			if (ThighFrame >= MaxFrames)
			{
				ThighFrame = 1;
				FootFrame = 1;
			}

		}
		else if (movingBackwards)
		{

			if (otherLegTurning) // other leg turning so we need to do a 3 or 4 frame offset 
			{
				
				ThighFrame--;
				FootFrame--;
	
				ThighFrame = ThighFrame - 3;
				FootFrame = FootFrame - 3;

				if (ThighFrame < 0)
				{
					ThighFrame = MaxFrames + ThighFrame;
					FootFrame = MaxFrames + FootFrame;
				}

			}
			else
			{
				ThighFrame--;
				FootFrame--;
				if (ThighFrame <= 0)
				{
					ThighFrame = MaxFrames - 1;
					FootFrame = MaxFrames - 1;
				}
			}
		}

		changeFrame = false;
		otherLegTurning = false;
	}

	// set the thigh and foot offsets according to the side of the tank they are using commands 
	
	// get offset for the current frame of the animation
	Vect TPos = myCommand->GetOffset(TankLegCommandBase::LegPart::Thigh, ThighFrame) * pMyTank->GetRTMatrix(); 
	Vect FPos = myCommand->GetOffset(TankLegCommandBase::LegPart::Foot, FootFrame) * pMyTank->GetRTMatrix();

	// get the local rotation for the thigh and foot 
	Matrix LocalTRot = Matrix(ROT_X, myCommand->GetRot(TankLegCommandBase::LegPart::Thigh, ThighFrame).X()) * 
		Matrix(ROT_Y, myCommand->GetRot(TankLegCommandBase::LegPart::Thigh, ThighFrame).Y()) *
		Matrix(ROT_Z, myCommand->GetRot(TankLegCommandBase::LegPart::Thigh, ThighFrame).Z());

	Matrix LocalFRot = Matrix(ROT_X, myCommand->GetRot(TankLegCommandBase::LegPart::Foot, FootFrame).X()) *
		Matrix(ROT_Y, myCommand->GetRot(TankLegCommandBase::LegPart::Foot, FootFrame).Y()) *
		Matrix(ROT_Z, myCommand->GetRot(TankLegCommandBase::LegPart::Foot, FootFrame).Z());

	// get the rotation of the tank 
	Matrix Rot = Matrix(RotType::ROT_X, pMyTank->GetRotation().X()) * Matrix(RotType::ROT_Y, pMyTank->GetRotation().Y()) * Matrix(RotType::ROT_Z, pMyTank->GetRotation().Z());

	// get the RotTrans matrix for the Thigh and foot
	TRotTrans = LocalTRot * Rot * Matrix(TRANS, TPos);
	FRotTrans = LocalFRot * Rot * Matrix(TRANS, FPos);

	Matrix ThighWorld = TScale * TRotTrans;
	Matrix FootWorld = FScale * FRotTrans;

	pGObj_Thigh->SetWorld(ThighWorld);
	pGObj_Foot->SetWorld(FootWorld);

	// animation cleanup

	movingBackwards = false;
	movingForwards = false;

}

void TankLeg::Draw()
{
	pGObj_Thigh->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	pGObj_Foot->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void TankLeg::OtherLegTurning()
{
	otherLegTurning = true;
}

void TankLeg::MoveForwards()
{
	movingForwards = true;
}

void TankLeg::MoveBackwards()
{
	movingBackwards = true;
}

// frame change alarms 
void TankLeg::Alarm0()
{
	changeFrame = true;
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, FrameRate); // reset alarm 
}
