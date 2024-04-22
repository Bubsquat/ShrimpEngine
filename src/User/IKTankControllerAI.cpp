// IK tank controller for ai enemies

#include "IKTankControllerAI.h"

#include "LevelManager.h"
#include "IKTank.h"

#include "../DataLogger.h"

IKTankControllerAI::IKTankControllerAI()
{
	SceneEntry();
}

IKTankControllerAI::~IKTankControllerAI()
{

}

void IKTankControllerAI::SceneEntry()
{
	SubmitUpdateRegistration();

	currentState = MOVING;
	wayPointNum = 0;
	alarmSet = false;
	playerSpotted = false;
	shootingFrames = 0;
	scanFrames = 0;
	scans = 0;
}

void IKTankControllerAI::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
}

void IKTankControllerAI::Update()
{

	// test if we see player tank 
	ScanForPlayer();

	// follow current patrol pattern (stinky method from last quarter, Im having a crisis)) 
	curTargetPoint = currentPattern->GetNextPos(wayPointNum, pTank->GetTrans().get(ROW_3));

	// this gets the distance to z (if we need to turn left or right)
	Vect norm = pTank->GetBodyWorld().get(MatrixRowType::ROW_0).getNorm();
	Matrix targetLocation = Matrix(TRANS, curTargetPoint);
	Vect toTarget = targetLocation.get(MatrixRowType::ROW_3) - pTank->GetBodyWorld().get(MatrixRowType::ROW_3);

	float distance = toTarget.dot(norm);
	//DataLogger::Add("Dist from Z :  %f", distance);

	travelBufferZone = 0.025f * GetDistToTarget(curTargetPoint);

	if (currentState != ENEMY_STATE::SCANNING)
	{
		if (GetDistToTarget(curTargetPoint) < 0)
		{
			if (distance < 0)
			{
				pTank->TurnRight();
			}
			else
			{
				pTank->TurnLeft();
			}
		}
		else
		{
			if (distance < -travelBufferZone)
			{
				pTank->TurnRight();
			}
			else if (distance > travelBufferZone)
			{
				pTank->TurnLeft();
			}
		}
	}

	// move towards target 

	switch (currentState) // gross!!
	{
	case MOVING:

		pTank->Forwards();

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

	case FIREING:

		pTank->Shoot();
		shootingFrames++;

		if (shootingFrames >= maxShootingFrames)
		{
			currentState = ENEMY_STATE::MOVING;
			shootingFrames = 0;
		}

		break;

	case SCANNING:

		scanFrames++;

		if (scanFrames >= maxScanFrames)
		{
			scanFrames = 0;
			scanDir = scanDir * -1;
			scans++;
		}

		if (scans == maxScans)
		{
			currentState = ENEMY_STATE::MOVING;
			scanFrames = 0;
		}

		if (scanDir == 1)
		{
			pTank->TurnRight();
		}
		else
		{
			pTank->TurnLeft();
		}

		break;
	}


}

void IKTankControllerAI::setTankToControl(IKTank* _Tank)
{
	pTank = _Tank;
}

void IKTankControllerAI::setPatrolPattern(PatrolPatternBase* p)
{
	currentPattern = p;
}

void IKTankControllerAI::ReportHit()
{
	LevelManager::UpdatePlayerScore(abs((pTank->GetTrans().get(ROW_3) - LevelManager::GetPlayerLocation()).mag()));
	LevelManager::RemoveEnemy();
	pTank->SceneExit();
	this->SceneExit();
}

void IKTankControllerAI::ScanForPlayer()
{

	float distToPlayer = (LevelManager::GetPlayerLocation() - pTank->GetTrans().get(ROW_3)).magSqr();
	//DataLogger::Add("Dist to player:  %f", distToPlayer);

	if (distToPlayer < detectionRange * detectionRange)
	{
		//DataLogger::Add("PlayerSpotted");
		playerSpotted = true;
		currentPattern = &persuePattern;
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	}

}

float IKTankControllerAI::GetDistToTarget(Vect TargetPoint)
{

	Vect norm = pTank->GetBodyWorld().get(ROW_2).getNorm();

	Vect toTarget = TargetPoint - pTank->GetTrans().get(ROW_3);

	return toTarget.dot(norm);

}

void IKTankControllerAI::Alarm0()
{
	currentState = ENEMY_STATE::SCANNING;
	alarmSet = false;
}

void IKTankControllerAI::Alarm1()
{
	currentState = ENEMY_STATE::FIREING;
	alarmSet = false;
}
