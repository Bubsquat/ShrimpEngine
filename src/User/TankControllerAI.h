// controller for tank that is controlled by game AI

#ifndef _TankControllerAI
#define _TankControllerAI

#include "TankControllerBaseClass.h"

class Tank;
class PatrolPatternBase;
class PersuePatrolPattern;
class Vect;

class TankControllerAI : public TankControllerBaseClass
{
public:

	enum TankState
	{
		SCANNING,
		MOVING,
		FIREING
	};

	TankControllerAI();
	TankControllerAI(const TankControllerAI&) = delete;
	TankControllerAI& operator = (const TankControllerAI&) = delete;
	~TankControllerAI();

	void Update();
	void SceneEntry();
	void SceneExit();

	void Alarm0();
	void Alarm1();

	void setTankToControl(Tank* _Tank);
	void setPatrolPattern(PatrolPatternBase* p);
	void ReportHit();

private:

	TankState myState;

	float getEnemyDistance();
	float getPointDistance(Vect point);
	float getEnemyDistanceTurret();

	Tank* pTank;
	bool scanning;
	bool playerSpotted;
	bool alarmSet;

	int wayPointNum;

	const float detectionRange = 50.0f; // range in which an enemy tank will see you if the turret is facing you  
	const float turretRotationSpeed = 0.05f;

	float travelBufferZone;
	float turretBufferZone;

	Matrix turretRot;

	PatrolPatternBase* currentPattern; 
	PersuePatrolPattern* persuePattern;

	Vect targetPoint;

	int scanningDeflections;
	int ScanAmt;
	float deflectionMultiplier = 1.4f;
	const int maxScanningDeflections = 80;
	const int maxScanAmt = 4;
	
	int shootingFrames;
	const int maxShootingFrames = 60;

};

#endif _TankControllerAI
