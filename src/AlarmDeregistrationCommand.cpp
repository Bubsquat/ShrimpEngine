// command for updating Alarm deregistration 

#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"
#include "RegistrationCommand.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* obj, AlarmableManager::ALARM_ID id)
	:ptrAlarmable(obj), id(id)
{}

void AlarmDeregistrationCommand::execute()
{
	AlarmableAttorney::Registration::SceneDeregistration(ptrAlarmable, id);
}