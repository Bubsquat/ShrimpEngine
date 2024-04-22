// controller for tank that is controlled by game AI

#include "TankControllerAI.h"
#include "LevelManager.h"
#include "Tank.h"
#include "TankTurret.h"
#include "PatrolPatternBase.h"
#include "PersuePatrolPattern.h"
#include "../DataLogger.h"
#include "PatrolPatternWaypointLoop.h"

TankControllerAI::TankControllerAI()
{

	pTank = nullptr;
	SubmitEntry();


	persuePattern= new PersuePatrolPattern();

}

TankControllerAI::~TankControllerAI()
{
	//delete currentPattern;
	delete persuePattern;

}


void TankControllerAI::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	wayPointNum = 1;
	targetPoint = currentPattern->GetNextPos(wayPointNum, Vect());
	turretRot = Matrix(ROT_Y, 0.0f);
	myState = MOVING;
	alarmSet = false;
	ScanAmt = 0;
	scanningDeflections = 0;
	playerSpotted = false;
	shootingFrames = 0;
}

void TankControllerAI::SceneExit()
{
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	Updateable::SubmitUpdateDeregistration();
}

void TankControllerAI::Update()
{
	// do we see a player

	if (!playerSpotted)
	{		
		float enemyDist = getEnemyDistanceTurret();

		if (enemyDist> 0.0f && enemyDist < detectionRange) // we see a player
		{
			playerSpotted = true;
			currentPattern = persuePattern;
			SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
		}

	}


	// face vehicle toward waypoint

	targetPoint = currentPattern->GetNextPos(wayPointNum, pTank->GetRTMatrix().get(MatrixRowType::ROW_3));

	//DataLogger::Add("wayPointNum : %i", wayPointNum);
	//DataLogger::Add("targetPoint X: %f Z : %f", targetPoint.X(), targetPoint.Z());
	//DataLogger::Add("Pos X: %f Z: %f", pTank->GetRTMatrix().get(MatrixRowType::ROW_3).X(), pTank->GetRTMatrix().get(MatrixRowType::ROW_3).Z());

	Matrix localRT = pTank->GetRTMatrix();
	Vect norm = localRT.get(MatrixRowType::ROW_0).getNorm();
	norm.W() = 0.0f;

	Matrix targetLocation = Matrix(TRANS, targetPoint);
	Vect toTarget = targetLocation.get(MatrixRowType::ROW_3) - localRT.get(MatrixRowType::ROW_3);
	toTarget.W() = 0.0f;

	float distance = toTarget.dot(norm);

	travelBufferZone = 0.025f * getPointDistance(targetPoint);

	if (getPointDistance(targetPoint) < 0)
	{
		if (distance < 0)
		{
			pTank->Right();
		}
		else
		{
			pTank->Left();

		}
	}
	else 
	{
		if (distance < -travelBufferZone)
		{
			pTank->Right();
		}
		else if (distance > travelBufferZone)
		{
			pTank->Left();
		}
	}

	// do the same for turrret 

	Matrix localTurret = pTank->GetTurret()->GetRTMatrix();
	norm = localTurret.get(MatrixRowType::ROW_0).getNorm();
	norm.W() = 0.0f;

	toTarget = targetLocation.get(MatrixRowType::ROW_3) - localTurret.get(MatrixRowType::ROW_3);
	toTarget.W() = 0.0f;

	float turretDeflectionDist = toTarget.dot(norm);

	Vect norm2 = localTurret.get(MatrixRowType::ROW_2).getNorm();
	norm2.W() = 0.0f;

	float turretDistance = toTarget.dot(norm2);

	turretBufferZone = 0.015f * turretDistance;

	if (turretDistance < 0)
	{
		if (turretDeflectionDist < 0)
		{
			turretRot *= Matrix(ROT_Y, -turretRotationSpeed);
		}
		else
		{
			turretRot *= Matrix(ROT_Y, turretRotationSpeed);
		}
	}
	else
	{
		if (turretDeflectionDist < -turretBufferZone)
		{
			turretRot *= Matrix(ROT_Y, -turretRotationSpeed);
		}
		else if (turretDeflectionDist > turretBufferZone)
		{
			turretRot *= Matrix(ROT_Y, turretRotationSpeed);
		}
	}

	//pTank->GetTurret()->Rot(turretRot);

	// move towards the target point 

	switch (myState) // ik this is gross, but its 1:30 am and im not about to make this a fsm 
	{
	case MOVING:

		pTank->Forwards();
		pTank->GetTurret()->Rot(turretRot);

		// decide when to scan 

		if (!alarmSet)
		{
			if (!playerSpotted)
			{
				SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.0f);
				alarmSet = true;
			}
			else
			{
				SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 3.0f);
				alarmSet = true;
			}
		}

		if (playerSpotted)
		{
			pTank->Shoot();
		}

		break;

	case SCANNING:

		// weird hackey animation 

		turretRot *= Matrix(ROT_Y, deflectionMultiplier * turretRotationSpeed);
		pTank->GetTurret()->Rot(turretRot);
		scanningDeflections++;

		if (scanningDeflections == maxScanningDeflections)
		{
			scanningDeflections = 0;
			deflectionMultiplier *= -1.0f;
			ScanAmt++;
		}

		if (ScanAmt == maxScanAmt)
		{
			myState = TankState::MOVING;

			scanningDeflections = 0;
			ScanAmt = 0;
		}

		break;

	case FIREING:

		pTank->GetTurret()->Rot(turretRot);
		pTank->Shoot();
		shootingFrames++;


		if (shootingFrames >= maxShootingFrames)
		{
			myState = TankState::MOVING;
			shootingFrames = 0;
		}


		break;
	}

}


void TankControllerAI::setTankToControl(Tank* _pTank)
{
	pTank = _pTank;
	pTank->SetController(this);
}

void TankControllerAI::setPatrolPattern(PatrolPatternBase* p)
{
	currentPattern = p;
}


float TankControllerAI::getEnemyDistance()
{

	Matrix localRT = pTank->GetRTMatrix();
	Vect norm = localRT.get(MatrixRowType::ROW_2).getNorm();
	norm.W() = 0.0f;

	Vect targetLocation = LevelManager::GetPlayerLocation();

	Vect toTarget = targetLocation - localRT.get(MatrixRowType::ROW_3);
	toTarget.W() = 0.0f;

	float distance = toTarget.dot(norm);
	//DataLogger::Add("Enemy Distance : %f", distance);

	return distance;

}

float TankControllerAI::getEnemyDistanceTurret()
{

	Matrix localRT = pTank->GetTurret()->GetRTMatrix();
	Vect norm = localRT.get(MatrixRowType::ROW_2).getNorm();
	norm.W() = 0.0f;

	Vect targetLocation = LevelManager::GetPlayerLocation();

	Vect toTarget = targetLocation - localRT.get(MatrixRowType::ROW_3);
	toTarget.W() = 0.0f;

	float distance = toTarget.dot(norm);
	//DataLogger::Add("Enemy Distance : %f", distance);

	return distance;

}

float TankControllerAI::getPointDistance(Vect point)
{
	Matrix localRT = pTank->GetRTMatrix();
	Vect norm = localRT.get(MatrixRowType::ROW_2).getNorm();
	norm.W() = 0.0f;

	Vect targetLocation = point;

	Vect toTarget = targetLocation - localRT.get(MatrixRowType::ROW_3);
	toTarget.W() = 0.0f;

	float distance = toTarget.dot(norm);
	//DataLogger::Add("Enemy Distance : %f", distance);

	return distance;

}

void TankControllerAI::ReportHit()
{
	LevelManager::UpdatePlayerScore(abs(getEnemyDistance()));
	LevelManager::RemoveEnemy();
	pTank->SceneExit();
	this->SceneExit();
}

void TankControllerAI::Alarm0()
{
	myState = TankState::SCANNING;

	alarmSet = false;
}

void TankControllerAI::Alarm1()
{
	myState = TankState::FIREING;
	alarmSet = false;
}