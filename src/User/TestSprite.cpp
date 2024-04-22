// class for testing sprite functionality 

#include "TestSprite.h"
#include "../SESpirte.h"
#include "../ImageManager.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../SpriteString.h"
#include "../SpriteFont.h"
#include "../SpriteFontManager.h"
#include "../DataLogger.h"

TestSprite::TestSprite()
{

	stitchRect = new Rect(0.0f, 0.0f, 300.0f, 400.0f);
	ImageManager::Load("stitch", TextureManager::Get("stitchImgTex"), stitchRect); // load the stitch text into an image 
	ImageManager::Load("dvdLogo", TextureManager::Get("dvdLogoTex"));

	sprite1 = new SESprite("dvdLogo"); // create new sprite 
	sprite1->SetAngle(3.15f);
	
	sprite2 = new SESprite("stitch");
	sprite2->SetPosition(Game::GetWidth() / 2.0f, Game::GetHeight() / 2.0f);
	
	offsetVar = 50.0f;

	//sFTest = new SpriteFont("Courier", "CourierNew");
	//sFTest = new SpriteFont("Impact", "Impact");
	SpriteFontManager::Load("Impact", "Impact");

	testLetter = 't';
	letterTest = SpriteFontManager::Get("Impact")->GetGlyph((char)testLetter);
	letterTest->SetPosition(static_cast<float>(Game::GetWidth()) - 100.0f, static_cast<float>(Game::GetHeight()) - 100.0f);

	spriteString = new SpriteString(SpriteFontManager::Get("Impact"), "HelpHelpHelp", 250.0f, 250.0f);

	// enter the scene 
	SubmitEntry();
}

TestSprite::~TestSprite()
{
	delete sprite1;
	delete sprite2;
	delete spriteString;

}

void TestSprite::SceneEntry()
{
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.0f);
	//Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 0.5f);
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
}

void TestSprite::SceneExit()
{
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
}

void TestSprite::Update()
{

	if (s1Pos.X() <= 0.0f || s1Pos.X() >= Game::GetWidth())
	{
		s1SpeedX = s1SpeedX * -1.0f;
	}
		
	if (s1Pos.Y() <= 0.0f || s1Pos.Y() >= Game::GetHeight())
	{
			s1SpeedY = s1SpeedY * -1.0f;
	}

	s1Pos.X() -= s1SpeedX;
	s1Pos.Y() -= s1SpeedY;

	sprite1->SetPosition(s1Pos.X(), s1Pos.Y());

	DataLogger::Add("Sprite 1 pos X: %f Y: %f", s1Pos.X(), s1Pos.Y());

	sprite2->SetAngle(s2Speed);

	DataLogger::Add("Sprite 2 rotSpeed : %f", s2Speed);

}

void TestSprite::Draw()
{}

void TestSprite::Draw2D()
{
	sprite2->Render();
	sprite1->Render();
	letterTest->Render();
	spriteString->Render();
}

void TestSprite::Alarm0()
{
	offsetVar = offsetVar * -1.0f;

	sprite2->SetCenter(offsetVar, 0.0f);
	sprite2->SetScalePixel(50.0f, 50.0f);

	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.0f);
}
