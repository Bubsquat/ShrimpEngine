// game object that contains the camera, sprites, and keydetection for the splash screen 

#include "SplashScreen.h"
#include "../ImageManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../CameraManager.h"
#include "IKTank.h"
#include "../SESpirte.h"
#include "../Game.h"
#include "../SpriteString.h"
#include "../SpriteFontManager.h"
#include "Demo2Level1Scene.h"

SplashScreen::SplashScreen(IKTank* _pTank, int _score)
{
	pTank = _pTank;
	score = _score;
	

	splashScreenGraphics = new SESprite("SplashScreen2Img");
	splashScreenGraphics->SetScalePixel(static_cast<float>(Game::GetWidth()), static_cast<float>(Game::GetHeight()));
	
	splashScreenGraphics->SetCenter(splashScreenGraphics->GetWidth() / 4.0f, splashScreenGraphics->GetHeight() / 4.0f);
	splashScreenGraphics->SetAngle(MATH_PI);

	// set up splash screen camera

	SSCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	SSCamera->setViewport(0, 0, Game::GetWidth(), Game::GetHeight());
	SSCamera->setPerspective(35.0f, float(Game::GetWidth()) / float(Game::GetHeight()), 1.0f, 100000.0f);

	camPos = Matrix(TRANS, 0.0f, 45.0f, 45.0f);
	camRot = Matrix(ROT_Y, 0.0f);

	lookAt.set(0.0f, 0.0f, 0.0f, 0.0f);
	camOffset = Matrix(TRANS, 0.0f, 1500.0f, 3500.0f);

	SSCamera->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), lookAt, camPos.get(MatrixRowType::ROW_3));
	SSCamera->updateCamera();

	//  set up scrolling text

	s1pos = Game::GetWidth() + 200.0f;
	s2pos = s1pos + 500.0f;
	s3pos = s2pos + 500.0f;

	string1 = new SpriteString(SpriteFontManager::Get("impact"), "PRESS [ SPACE] TO START", s1pos , textHeight);
	string2 = new SpriteString(SpriteFontManager::Get("impact"), "PRESS [ SPACE] TO START", s2pos, textHeight);
	string3 = new SpriteString(SpriteFontManager::Get("impact"), "Twice the walking!!", s3pos, textHeight);

	// is there a score?

	scoreString = new SpriteString(SpriteFontManager::Get("impact"), "L A S T   S C O R E : " + std::to_string(score), (static_cast<float>(Game::GetWidth()) / 2.0f) + 100.0f, (static_cast<float>(Game::GetHeight()) / 2.0f) - 100.0f);

	// enter scene 

	SubmitEntry();
}

SplashScreen::~SplashScreen()
{
	delete splashScreenGraphics;
	delete SSCamera;
	delete string1;
	delete string2;
	delete string3;
	delete scoreString;
}

void SplashScreen::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(SSCamera);
}

void SplashScreen::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
}

void SplashScreen::Update()
{

	// update text pos

	s1pos -= textSpeed;
	s2pos -= textSpeed;
	s3pos -= textSpeed;

	if (s1pos < -200.0f) s1pos = textOrigin;
	if (s2pos < -200.0f) s2pos = textOrigin;
	if (s3pos < -200.0f) s3pos = textOrigin;

	// update camera 
	camRot = Matrix(ROT_Y, camRotSpeed) * camRot;

	camPos =  camOffset * camRot * Matrix(TRANS, pTank->GetTrans().get(MatrixRowType::ROW_3));
	lookAt.set(pTank->GetTrans().get(MatrixRowType::ROW_3).X(), pTank->GetTrans().get(MatrixRowType::ROW_3).Y(), pTank->GetTrans().get(MatrixRowType::ROW_3).Z(), 0.0f);

	SSCamera->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), lookAt, camPos.get(MatrixRowType::ROW_3));

	SSCamera->updateCamera();

}

void SplashScreen::Draw()
{

}

void SplashScreen::Draw2D()
{

	splashScreenGraphics->Render(SceneManager::GetCurrentScene()->GetCameraManager()->Get2DCamera());
	string1->Set(s1pos, textHeight);
	string1->Render();
	string2->Set(s2pos, textHeight);
	string2->Render();
	string3->Set(s3pos, textHeight);
	string3->Render();

	if (score != -1)
	{
		scoreString->Render();
	}
}

void SplashScreen::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE) // start game here (scene change)
	{
		SceneManager::SubmitSceneChange(new Demo2Level1Scene());
	}
}