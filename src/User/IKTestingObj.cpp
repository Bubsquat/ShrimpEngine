// game object for testing ik system features

#include "IKTestingObj.h"

#include "../ModelManager.h"
#include "../ShaderManager.h"
#include "../SceneManager.h"
#include "../CameraManager.h"
#include "../Colors.h"
#include "../Segment.h"
#include "../Linkage.h"
#include "../InverseKinematics.h"
#include "../Visualizer.h"
#include "../DataLogger.h"

#include "TestMover.h"

IKTestingObj::IKTestingObj()
{
	// set up a box
	Vect boxColor = Colors::Gray;
	pGoTestBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("boxModel"), ShaderManager::Get("constantColor"), boxColor);
	pGoTestBox2 = new GraphicsObject_ColorNoTexture(ModelManager::Get("boxModel"), ShaderManager::Get("constantColor"));
	boxScale = Matrix(SCALE, 80.0f, 80.0f, 150.0f);
	boxWorld = boxScale * Matrix(TRANS, 0, 0, 0);
	box2World = boxWorld;

	pGoTestBox->SetWorld(boxWorld);
	pGoTestBox2->SetWorld(box2World);

	// make a linkage
	linkage1 = new Linkage(2, 150.0f, Vect(-10.0f, 0.0f, 20.0f), Vect(0, 0, 1));

	//linkage1->RotSegment(2, Matrix(ROT_X, 0.5f));

	//targetPoint = Vect(50.0f, 55.0f, 100.0f);
	targetPoint = Vect(15.0f, 60.0f, 130.0f);

 	SceneEntry();
}

IKTestingObj::~IKTestingObj()
{
 
	delete linkage1;
	delete pGoTestBox;
	delete pGoTestBox2;
}

void IKTestingObj::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	//Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.5f);
	//Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 0.0625f);

	InverseKinematics::ApplyTransforms2Link(linkage1, targetPoint);
}

void IKTestingObj::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
}

void IKTestingObj::Update()
{
	targetPoint = mover->MoverPosition();
	InverseKinematics::ApplyTransforms2Link(linkage1, targetPoint);

	///*
	box2World = boxScale * linkage1->GetSegment(0)->GetAlignmentMatrix();
	boxWorld = boxScale * linkage1->GetSegment(1)->GetAlignmentMatrix();
	
	pGoTestBox->SetWorld(boxWorld);
	pGoTestBox2->SetWorld(box2World);

	//*/


	Visualizer::ShowMarker(targetPoint);
	//linkage1->GetSegment(0)->PrintSegment();
	//linkage1->GetSegment(1)->PrintSegment();

}

void IKTestingObj::Draw()
{
	pGoTestBox->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	pGoTestBox2->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	linkage1->ShowLinks();

}

void IKTestingObj::Alarm0()
{

	InverseKinematics::ApplyTransforms2Link(linkage1, targetPoint);
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 2.5f);

}

void IKTestingObj::Alarm1()
{
	linkage1->RotSegment(2, Matrix(ROT_Z, 0.3f));
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 0.0625f);
}

void IKTestingObj::setTestMover(TestMover* _mover)
{
	mover = _mover;
}
