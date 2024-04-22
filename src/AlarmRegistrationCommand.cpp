// command for updating Alarm registration 

#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"
#include "RegistrationCommand.h"


AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* obj, AlarmableManager::ALARM_ID id)
	:ptrAlarmable(obj), id(id)
{}

void AlarmRegistrationCommand::setTime(float t)
{
	this->time = t;
}

void AlarmRegistrationCommand::execute()
{
	AlarmableAttorney::Registration::SceneRegistration(ptrAlarmable, id, time);
}

