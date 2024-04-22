// mananger for alarmable objects

#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "RegistrationStateEnum.h"
#include "TimeManager.h"
AlarmableManager::~AlarmableManager()
{
	this->alarmMap.clear();
}


void AlarmableManager::ProcessAlarms()
{

	AlarmMapRef it = alarmMap.begin();

	while (it != alarmMap.end() && (*it).first <= TimeManager::GetTime()) // run through alarms that should be triggered 
	{
		// this happens for every alarm that should be triggered
		Alarmable* currAlarmable = (*it).second.first;
		AlarmableManager::ALARM_ID currId = (*it).second.second;

		it++; // it is here incase triggering alarm causes it to be deleted

		AlarmableAttorney::GameLoop::TriggerAlarm(currAlarmable, currId); // trigger the alarm that must be triggered 
		//currAlarmable->SubmitAlarmDeregistration(currId); // deregister triggered alarm

	}

}

void AlarmableManager::Register(float t, Alarmable* obj, ALARM_ID id)
{
	AlarmEvent newEvent = { obj, id };
	AlarmableAttorney::GameLoop::SetDeleteRef(obj, alarmMap.emplace(t, newEvent), id);
}

void AlarmableManager::Deregister(Alarmable* obj, ALARM_ID id)
{
	alarmMap.erase(AlarmableAttorney::GameLoop::GetDeleteRef(obj, id));
}
