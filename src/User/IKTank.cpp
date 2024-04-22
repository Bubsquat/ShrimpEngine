// demo game tank that uses the IK system to walk on terrain 

#include "IKTank.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "../SceneManager.h"
#include "../CameraManager.h"
#include"../HeightmapTerrain.h"
#include "../Linkage.h"
#include "../Segment.h"
#include "../InverseKinematics.h"
#include "../SMathTools.h"
#include "BulletFactory.h"
#include "IKTankController.h"

#include "Plane.h"
#include "../Visualizer.h"
#include "../DataLogger.h"

IKTank::IKTank(Vect startPos)
{

	// set up graphics objects 
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGO_TankBody = new GraphicsObject_TextureLight(ModelManager::Get("IKTankBodyModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);
	pGO_TankTurret = new GraphicsObject_TextureLight(ModelManager::Get("IKTankTurretModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);
	pGO_TankLowerLeg = new GraphicsObject_TextureLight(ModelManager::Get("IKTankLowerLegModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);
	pGO_TankUpperLeg = new GraphicsObject_TextureLight(ModelManager::Get("IKTankUpperLegModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);

	// set up world
	Scale = Matrix(SCALE, 0.5f, 0.5f, 0.5f);
	Rot = Matrix(IDENTITY);
	Trans = Matrix(TRANS, startPos);
	AlignMat = Matrix(IDENTITY);
	BodyRot = Matrix(IDENTITY);
	World = Scale * Rot * Trans;
	turretWorld = Scale * Rot * Trans;

	pGO_TankBody->SetWorld(World);
	pGO_TankTurret->SetWorld(turretWorld);

	pGO_TankLowerLeg->SetWorld(World); // this is just for construction, IK will set it
	pGO_TankUpperLeg->SetWorld(World);

	// set collider model 
	Collidable::SetColliderModel(pGO_TankBody->getModel(), VOLUME_TYPE::OBB);
	SetCollidableGroup<IKTank>();

	// leg stuff 

	RFLinkage = new Linkage(2, 100.0f, RFLegOffset + startPos, Vect(1, 0, 0));
	RBLinkage = new Linkage(2, 100.0f, RBLegOffset + startPos, Vect(1, 0, 0));
	LFLinkage = new Linkage(2, 100.0f, LFLegOffset + startPos, Vect(-1, 0, 0));
	LBLinkage = new Linkage(2, 100.0f, LBLegOffset + startPos, Vect(-1, 0, 0));

	SceneEntry();
}

IKTank::~IKTank()
{
	delete RFLinkage;
	delete RBLinkage;
	delete LFLinkage;
	delete LBLinkage;

	delete pGO_TankBody;
	delete pGO_TankTurret;
	delete pGO_TankLowerLeg;
	delete pGO_TankUpperLeg;
}

void IKTank::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	

	RFTargetVect = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	RBTargetVect = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	LFTargetVect = Vect(-1.0f, 0.0f, 0.0f, 0.0f);
	LBTargetVect = Vect(-1.0f, 0.0f, 0.0f, 0.0f);

	RFDir = 1;
	RBDir = -1;
	LFDir = 1;
	LBDir = -1;

	RFAngle = 0;
	RBAngle = 0;
	LFAngle = 0;
	LBAngle = 0;

	RFY = 0.0f;
	RBY = 0.0f;
	LFY = 0.0f;
	LBY = 0.0f;

	turretDeflect = 0;

	canFire = true; 

	Collidable::UpdateCollisionData(World);

	SubmitCollisionRegistration();
}

void IKTank::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
}

void IKTank::Update()
{

	// update body position 
	SetBodyPos();

	World = Scale * Rot * AlignMat *  Trans;
	pGO_TankBody->SetWorld(World);

	Collidable::UpdateCollisionData(World);

	// update turret position

	turretAlign = Matrix(ROT_ORIENT, World.get(ROW_2), Vect(0, 1, 0));
	turretWorld = Scale * Matrix(ROT_X, turretDeflect) * Matrix(TRANS, TurretOffset) * turretAlign * Trans;
	//turretWorld = Scale * Rot * Trans * Matrix(TRANS, TurretOffset);
	pGO_TankTurret->SetWorld(turretWorld);

	// update leg pos 
	RFLegPos = RFLegOffset * Rot * AlignMat * Trans;
	RBLegPos = RBLegOffset * Rot * AlignMat * Trans;
	LFLegPos = LFLegOffset * Rot * AlignMat * Trans;
	LBLegPos = LBLegOffset * Rot * AlignMat * Trans;

	RFLinkage->TransformLinkage(Matrix( TRANS, RFLegPos - RFLinkage->GetSegment(0)->GetStartPoint()));
	RBLinkage->TransformLinkage(Matrix(TRANS, RBLegPos - RBLinkage->GetSegment(0)->GetStartPoint()));
	LFLinkage->TransformLinkage(Matrix(TRANS, LFLegPos - LFLinkage->GetSegment(0)->GetStartPoint()));
	LBLinkage->TransformLinkage(Matrix(TRANS, LBLegPos - LBLinkage->GetSegment(0)->GetStartPoint()));

	RFTargetPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(RFLegPos + 100 * (RFTargetVect));
	RBTargetPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(RBLegPos + 100 * (RBTargetVect));
	LFTargetPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(LFLegPos + 100 * (LFTargetVect));
	LBTargetPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(LBLegPos + 100 * (LBTargetVect));

	// add height offsets 
	
	RFTargetPos.Y() += RFY;
	RBTargetPos.Y() += RBY;
	LFTargetPos.Y() += LFY;
	LBTargetPos.Y() += LBY;

	// do the IK solves 

	InverseKinematics::ApplyTransforms2Link(RFLinkage, RFTargetPos);
	InverseKinematics::ApplyTransforms2Link(RBLinkage, RBTargetPos);
	InverseKinematics::ApplyTransforms2Link(LFLinkage, LFTargetPos);
	InverseKinematics::ApplyTransforms2Link(LBLinkage, LBTargetPos);

}

void IKTank::Draw()
{

	pGO_TankBody->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	pGO_TankTurret->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	// render all the legs 
	Matrix LowerLegWorld = LowerLegScale * Matrix(ROT_X, -MATH_PI / 2) * RFLinkage->GetSegment(1)->GetAlignmentMatrix();
	pGO_TankLowerLeg->SetWorld(LowerLegWorld);
	pGO_TankLowerLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	LowerLegWorld = LowerLegScale * Matrix(ROT_X, -MATH_PI / 2) * RBLinkage->GetSegment(1)->GetAlignmentMatrix();
	pGO_TankLowerLeg->SetWorld(LowerLegWorld);
	pGO_TankLowerLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	LowerLegWorld = LowerLegScale * Matrix(ROT_X, -MATH_PI / 2) * LFLinkage->GetSegment(1)->GetAlignmentMatrix();
	pGO_TankLowerLeg->SetWorld(LowerLegWorld);
	pGO_TankLowerLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	LowerLegWorld = LowerLegScale * Matrix(ROT_X, -MATH_PI / 2) * LBLinkage->GetSegment(1)->GetAlignmentMatrix();
	pGO_TankLowerLeg->SetWorld(LowerLegWorld);
	pGO_TankLowerLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());


	Matrix UpperLegWorld = UpperLegScale * Matrix(ROT_X, -MATH_PI / 2) * RFLinkage->GetSegment(0)->GetAlignmentMatrix();
	pGO_TankUpperLeg->SetWorld(UpperLegWorld);
	pGO_TankUpperLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	UpperLegWorld = UpperLegScale * Matrix(ROT_X, -MATH_PI / 2) * RBLinkage->GetSegment(0)->GetAlignmentMatrix();
	pGO_TankUpperLeg->SetWorld(UpperLegWorld);
	pGO_TankUpperLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	UpperLegWorld = UpperLegScale * Matrix(ROT_X, -MATH_PI / 2) * LFLinkage->GetSegment(0)->GetAlignmentMatrix();
	pGO_TankUpperLeg->SetWorld(UpperLegWorld);
	pGO_TankUpperLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	UpperLegWorld = UpperLegScale * Matrix(ROT_X, -MATH_PI / 2) * LBLinkage->GetSegment(0)->GetAlignmentMatrix();
	pGO_TankUpperLeg->SetWorld(UpperLegWorld);
	pGO_TankUpperLeg->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

}

void IKTank::Collision(Bullet*)
{

	myController->ReportHit();

}

void IKTank::SetBulletFactory(BulletFactory* bf)
{
	myBulletFactory = bf;
}

void IKTank::SetController(IKTankController* pCon)
{
	this->myController = pCon;
}

void IKTank::Forwards()
{
	Trans = Matrix(TRANS,  (Matrix(TRANS, Vect(0,0,forwardsMoveSpeed)) * Rot * AlignMat * Trans).get(ROW_3));

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);
}

void IKTank::Backwards()
{

	Trans = Matrix(TRANS, (Matrix(TRANS, Vect(0, 0, -forwardsMoveSpeed)) * Rot * AlignMat * Trans).get(ROW_3));

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);
}

void IKTank::Left()
{
	Trans = Matrix(TRANS, (Matrix(TRANS, Vect(horizontalMoveSpeed, 0, 0)) * Rot * AlignMat * Trans).get(ROW_3));

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);

}

void IKTank::Right()
{
	Trans = Matrix(TRANS, (Matrix(TRANS, Vect(-horizontalMoveSpeed, 0, 0)) * Rot * AlignMat * Trans).get(ROW_3));

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);

}

void IKTank::TurnLeft()
{
	Rot = Matrix(ROT_Y, rotSpeed) * Rot;

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);
}

void IKTank::TurnRight()
{
	Rot = Matrix(ROT_Y, -rotSpeed) * Rot;

	advanceWalkVector(RIGHT_FRONT);
	advanceWalkVector(RIGHT_BACK);
	advanceWalkVector(LEFT_FRONT);
	advanceWalkVector(LEFT_BACK);

}

void IKTank::DeflectUp()
{
	turretDeflect -= deflectSpeed;
	turretDeflect = SMathTools::Clamp(turretDeflect, MinDeflect, MaxDeflect);
}

void IKTank::DeflectDown()
{
	turretDeflect += deflectSpeed;
	turretDeflect = SMathTools::Clamp(turretDeflect, MinDeflect, MaxDeflect);
}

void IKTank::Shoot()
{

	if (canFire)
	{
		Matrix bulletMat = Matrix(TRANS, bulletOffset) * Matrix(ROT_X, turretDeflect) * turretAlign * Trans;
		myBulletFactory->CreateBullet(bulletMat);

		canFire = false;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.5f);
	}

}

Matrix IKTank::GetRot()
{
	return this->Rot;
}

Matrix IKTank::GetTrans()
{
	return this->Trans;
}

Matrix IKTank::GetBodyWorld()
{
	return World;
}

Matrix IKTank::GetTurretWorld()
{
	return turretWorld;
}

Matrix IKTank::GetAlignMat()
{
	return AlignMat;
}


void IKTank::Alarm0()
{
	canFire = true;
}

// private functions for handling animation

void IKTank::SetBodyPos()
{

	// get terrain point 
	Vect terrainPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(Trans.get(ROW_3));

	// calculate the y position the model should be 
	float yVal = Yoffset - (Trans.get(ROW_3).Y() - terrainPos.Y());

	// get rotation to align with terrain normal
	Vect terrainNormal = SceneManager::GetCurrentScene()->GetTerrain()->GetNormal(Trans.get(ROW_3));
	AlignMat = Matrix(ROT_ORIENT, terrainNormal, (Rot * Trans).get(ROW_2).getNorm());
	AlignMat = Matrix(ROT_Y, MATH_PI) * Matrix(ROT_X, MATH_PI / 2) * AlignMat;

	Trans = Matrix(TRANS, Vect(0.0f, yVal, 0.0f)) *	Trans;

}


void IKTank::advanceWalkVector(LEGS leg)
{

	switch (leg)
	{

	case LEGS::RIGHT_FRONT:

		RFAngle += RFDir * LegTravel;
		if (abs(RFAngle) >= MaxAngle) RFDir = -1 * RFDir;
		RFTargetVect = World.get(ROW_0) * Matrix(ROT_Y, RFAngle);
		RFTargetVect.norm();

		RFY += -RFDir * LegRaiseSpeed;
		RFY = SMathTools::Clamp(RFY, 0.0f, TargetYOffset);

		break;

	case LEGS::RIGHT_BACK:

		RBAngle += RBDir * LegTravel;
		if (abs(RBAngle) >= MaxAngle) RBDir = -1 * RBDir;
		RBTargetVect = World.get(ROW_0) * Matrix(ROT_Y, RBAngle);
		RBTargetVect.norm();

		RBY += -RBDir * LegRaiseSpeed;
		RBY = SMathTools::Clamp(RBY, 0.0f, TargetYOffset);

		break;

	case LEGS::LEFT_FRONT:

		LFAngle += LFDir * LegTravel;
		if (abs(LFAngle) >= MaxAngle) LFDir = -1 * LFDir;
		LFTargetVect = -World.get(ROW_0) * Matrix(ROT_Y, LFAngle);
		LFTargetVect.norm();

		LFY += LFDir * LegRaiseSpeed;
		LFY = SMathTools::Clamp(LFY, 0.0f, TargetYOffset);

		break;

	case LEGS::LEFT_BACK:

		LBAngle += LBDir * LegTravel;
		if (abs(LBAngle) >= MaxAngle) LBDir = -1 * LBDir;
		LBTargetVect = -World.get(ROW_0) * Matrix(ROT_Y, LBAngle);
		LBTargetVect.norm();

		LBY +=  LBDir * LegRaiseSpeed;
		LBY = SMathTools::Clamp(LBY, 0.0f, TargetYOffset);

		break;

	}

}

