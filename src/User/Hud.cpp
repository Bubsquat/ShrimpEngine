// class for handleing game hud elements

#include "Hud.h"

#include "../SESpirte.h"
#include "../Game.h"
#include "../SpriteString.h"
#include "../SpriteFontManager.h"
#include "../ImageManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../CameraManager.h"
#include "LevelManager.h"

Hud::Hud()
{




	hudSprite = new SESprite("hudImg");
	hudSprite->SetScalePixel(static_cast<float>(Game::GetWidth()), static_cast<float>(Game::GetHeight()));

	hudSprite->SetCenter(hudSprite->GetWidth() / 4.0f, hudSprite->GetHeight() / 4.0f);
	hudSprite->SetAngle(MATH_PI);

	// set up the health chunks 

	float Yoffset = -50.0f;

	for (int i = 4; i >= 0; i--)
	{
		SESprite* newSprite = new SESprite("healthChunkImg");
		newSprite->SetScalePixel(static_cast<float>(Game::GetWidth()), static_cast<float>(Game::GetHeight()));
		newSprite->SetCenter(hudSprite->GetWidth() / 4.0f, hudSprite->GetHeight() / 4.0f);
		newSprite->SetAngle(MATH_PI);
		newSprite->SetPosition(0.0f, i * Yoffset);

		healthChunks.push_back(newSprite);
	}

	playerHealth = 5;

	numEnemiesX = 45.0f;
	numEnemiesY = Game::GetHeight() - 30.0f;

	numEnemies = new SpriteString(SpriteFontManager::Get("impact"), "0", numEnemiesX, numEnemiesY);

	LSActive = false;
	KActive = false;
	PBActive = false;

	LongShot.set(180.0f, 15.0f, 0.0f);
	PointBlank.set(180.0f, 15.0f, 0.0f);
	Kill.set(100.0f, 15.0f, 0.0f);

	LongShotString = new SpriteString(SpriteFontManager::Get("impact"), "LONG SHOT ! ", LongShot.X(), LongShot.Y());
	PointBlankString = new SpriteString(SpriteFontManager::Get("impact"), "POINT BLANK ! ", PointBlank.X(), PointBlank.Y());
	KillString = new SpriteString(SpriteFontManager::Get("impact"), "KI L L", Kill.X(), Kill.Y());

	SubmitEntry();
}

Hud::~Hud()
{
	delete hudSprite;
	delete KillString;
	delete LongShotString;
	delete PointBlankString;
	delete numEnemies;

	while (!healthChunks.empty())
	{
		delete healthChunks.front();
		healthChunks.pop_front();
	}
}

void Hud::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	tookDamage = false;
	currentDFrame = 0;
}

void Hud::SceneExit()
{
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_2);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_3);
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
}

void Hud::Update()
{

	if (LSActive)
	{
		LongShot.Y() += textRiseSpeed;
		LongShotString->Set(LongShot.X(), LongShot.Y());
	}
	if (PBActive) 
	{
		PointBlank.Y() += textRiseSpeed;
		PointBlankString->Set(PointBlank.X(), PointBlank.Y());
	} 
	if (KActive)
	{
		Kill.Y() += textRiseSpeed;
		KillString->Set(Kill.X(), Kill.Y());
	}

	numEnemies->Set(SpriteFontManager::Get("impact"), std::to_string(LevelManager::GetEnemyNumber()), numEnemiesX, numEnemiesY);
	
	if (tookDamage) // shake hud to indicate damage taken 
	{
		hudSprite->SetPosition(DamagePositions[currentDFrame].X(), DamagePositions[currentDFrame].Y());
		currentDFrame++;
		if (currentDFrame == maxDFrames) currentDFrame = 0;

		
	}



}

void Hud::Draw2D()
{
	hudSprite->Render();

	// only render the health we have

	HealthChunkList::iterator it = healthChunks.begin();
	for (int i = 0; i < playerHealth; i++)
	{
		(*it)->Render();
		it++;
	}

	numEnemies->Render();

	if (LSActive) LongShotString->Render();
	if (PBActive) PointBlankString->Render();
	if (KActive) KillString->Render();

}

void Hud::SetPlayerHealth(int _health)
{

	if (_health < playerHealth)
	{
		tookDamage = true;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_3, 0.3f);
	}

	playerHealth = _health;

}

void Hud::ReportKill(KillType kt)
{

	switch (kt)
	{

	case KillType::KILL:
		Kill.set(100.0f, 15.0f, 0.0f);
		KActive = true;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.0f);
		break;
	case KillType::LONGSHOT:
		LongShot.set(180.0f, 15.0f, 0.0f);
		LSActive = true;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 2.0f);
		break;
	case KillType::POINTBLANK:
		PointBlank.set(180.0f, 15.0f, 0.0f);
		PBActive = true;
		SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_2, 2.0f);
		break;

	}
}

void Hud::Alarm0()
{
	KActive = false;
}
void Hud::Alarm1()
{
	LSActive = false;
}
void Hud::Alarm2()
{
	PBActive = false;
}

void Hud::Alarm3()
{
	tookDamage = false;
	hudSprite->SetPosition(0.0f, 0.0f);
}

