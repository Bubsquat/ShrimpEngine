// attribute that allows game object to have alarms

#include "Alarmable.h"
#include "RegistrationStateEnum.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include <assert.h>
#include "TimeManager.h"

Alarmable::Alarmable()
{
	
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		RegData[i].currentState = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].pRegCmd = new AlarmRegistrationCommand(this, AlarmableManager::ALARM_ID(i));
		RegData[i].pDeregCmd = new AlarmDeregistrationCommand(this, AlarmableManager::ALARM_ID(i));
	}

}

Alarmable::~Alarmable()
{

	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		delete RegData[i].pRegCmd;
		delete RegData[i].pDeregCmd;
	}

}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{

	switch (id) // stinky switch I should replace later 
	{
	case AlarmableManager::ALARM_ID::ALARM_0:
		RegData[0].currentState = RegistrationState::PENDING_DEREGISTRATION;
		this->SceneDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_ID::ALARM_1:
		RegData[1].currentState = RegistrationState::PENDING_DEREGISTRATION;
		this->SceneDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_ID::ALARM_2:
		RegData[2].currentState = RegistrationState::PENDING_DEREGISTRATION;
		this->SceneDeregistration(AlarmableManager::ALARM_ID::ALARM_2);
		this->Alarm2();
		break;
	case AlarmableManager::ALARM_ID::ALARM_3:
		RegData[3].currentState = RegistrationState::PENDING_DEREGISTRATION;
		this->SceneDeregistration(AlarmableManager::ALARM_ID::ALARM_3);
		this->Alarm3();
		break;
	case AlarmableManager::ALARM_ID::ALARM_4:
		RegData[3].currentState = RegistrationState::PENDING_DEREGISTRATION;
		this->SceneDeregistration(AlarmableManager::ALARM_ID::ALARM_3);
		this->Alarm4();
		break;
	default:
		assert("Error No Alarm Triggered");
		break;
	}

}

void Alarmable::SceneRegistration(AlarmableManager::ALARM_ID id, float t)
{
	assert(RegData[static_cast<int>(id)].currentState == RegistrationState::PENDING_REGISTRATION);

	//SceneManager::GetCurrentScene()->Register(this, id, t);
	SceneAttorney::Registration::Register(SceneManager::GetCurrentScene(), this, id, t);

	RegData[static_cast<int>(id)].currentState = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::SceneDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[static_cast<int>(id)].currentState == RegistrationState::PENDING_DEREGISTRATION);

	//SceneManager::GetCurrentScene()->Deregister(this, id);
	SceneAttorney::Registration::Deregister(SceneManager::GetCurrentScene(), this, id);

	RegData[static_cast<int>(id)].currentState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float t)
{
	
	// convert to actual time here  
	assert(RegData[static_cast<int>(id)].currentState == RegistrationState::CURRENTLY_DEREGISTERED);
	RegData[static_cast<int>(id)].pRegCmd->setTime(TimeManager::GetTime() + t); // must set time to command here 

	//SceneManager::GetCurrentScene()->SubmitCommand(RegData[static_cast<int>(id)].pRegCmd);
	SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), RegData[static_cast<int>(id)].pRegCmd);

	RegData[static_cast<int>(id)].currentState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	//assert(RegData[static_cast<int>(id)].currentState == RegistrationState::CURRENTLY_REGISTERED);

	if (RegData[static_cast<int>(id)].currentState == RegistrationState::CURRENTLY_REGISTERED) // only submit dereg if its already registered 
	{
		//SceneManager::GetCurrentScene()->SubmitCommand(RegData[static_cast<int>(id)].pDeregCmd);
		SceneAttorney::Registration::SubmitCommand(SceneManager::GetCurrentScene(), RegData[static_cast<int>(id)].pDeregCmd);

		RegData[static_cast<int>(id)].currentState = RegistrationState::PENDING_DEREGISTRATION;
	}


}

void Alarmable::SetDeleteRef(AlarmableManager::AlarmMapRef ref, AlarmableManager::ALARM_ID id)
{
	RegData[static_cast<int>(id)].myDeleteRef = ref;
}

AlarmableManager::AlarmMapRef Alarmable::GetDeleteRef(AlarmableManager::ALARM_ID id)
{
	return RegData[static_cast<int>(id)].myDeleteRef;
}


// user defined alarm functions 
void Alarmable::Alarm0()
{
	// do nothing 
}
void Alarmable::Alarm1()
{
	// do nothing 
}
void Alarmable::Alarm2()
{
	// do nothing 
}
void Alarmable::Alarm3()
{
	// do nothing 
}
void Alarmable::Alarm4()
{
	// do nothing 
}
