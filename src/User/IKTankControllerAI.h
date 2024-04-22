// IK tank controller for ai enemies 
	
#ifndef _IKTankControllerAI
#define _IKTankControllerAI
	
#include "IKTankController.h"
#include "PatrolPatternBase.h"
#include "PersuePatrolPattern.h"
	
class IKTankControllerAI : public IKTankController
{
public :
	
	IKTankControllerAI();
	IKTankControllerAI(const IKTankControllerAI&) = delete;
	IKTankControllerAI & operator= (const IKTankControllerAI&) = delete;
	~IKTankControllerAI();
	
	void Update();
	void SceneEntry();
	void SceneExit();

	void setTankToControl(IKTank* _Tank);
	void setPatrolPattern(PatrolPatternBase* p);
	void ReportHit();

	void Alarm0();
	void Alarm1();

private:
	
	enum ENEMY_STATE
	{
		MOVING,
		SCANNING,
		FIREING
	};

	ENEMY_STATE currentState;
	
	IKTank* pTank;
	PatrolPatternBase* currentPattern; 
	PersuePatrolPattern persuePattern;

	Vect curTargetPoint;

	const float detectionRange = 3000.0f; 
	const float targetReachedRange = 100.0f;

	float travelBufferZone;

	void ScanForPlayer();
	float GetDistToTarget(Vect TargetPoint);

	int wayPointNum;

	bool alarmSet;
	bool playerSpotted;
	int shootingFrames;
	const int maxShootingFrames = 140;

	int scanFrames;
	int scans;
	const int maxScans = 4;
	const int maxScanFrames = 120;
	int scanDir = 1;


};
	
#endif _IKTankControllerAI

