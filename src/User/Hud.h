// class for handleing game hud elements

#ifndef _Hud
#define _Hud

#include "../GameObject.h"
#include <list>

class SESprite;
class SpriteString;

class Hud : public GameObject
{
public:

	Hud();
	Hud(const Hud&) = delete;
	Hud& operator= (const Hud&) = delete;
	~Hud();

	void SceneEntry();
	void SceneExit();
	void Update();
	void Draw2D();

	void SetPlayerHealth(int health);

	enum KillType
	{
		LONGSHOT,
		POINTBLANK,
		KILL
	};

	void ReportKill(KillType kt);

	void Alarm0();
	void Alarm1();
	void Alarm2();
	void Alarm3();

private:

	SESprite* hudSprite;
	using HealthChunkList = std::list<SESprite*>;
	HealthChunkList healthChunks;
	int playerHealth;
	SpriteString* numEnemies;

	float numEnemiesX;
	float numEnemiesY;

	SpriteString* LongShotString;
	SpriteString* KillString;
	SpriteString* PointBlankString; 

	Vect LongShot;
	Vect Kill;
	Vect PointBlank; 

	bool LSActive;
	bool KActive;
	bool PBActive;

	const float textRiseSpeed = 3.0f;

	bool tookDamage;

	const int maxDFrames = 6;
	int currentDFrame;
	Vect DamagePositions[6] {

		Vect(2.0f, 2.0f, 0.0f),
		Vect(-1.0f, 3.0f, 0.0f),
		Vect(-2.0f, -2.0f, 0.0f),
		Vect(-1.0f, 3.0f, 0.0f),
		Vect(0.0f, -1.0f, 0.0f),
		Vect(2.0f, 2.0f, 0.0f)
	};


};


#endif _Hud

