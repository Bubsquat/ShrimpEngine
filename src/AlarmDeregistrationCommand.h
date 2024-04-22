// command for updating alarm deregistration 

#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "RegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public RegistrationCommand
{
public:

	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(Alarmable* cmd, AlarmableManager::ALARM_ID id);
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator =(const AlarmDeregistrationCommand&) = delete;
	~AlarmDeregistrationCommand() = default;

	void execute();

private:

	Alarmable* ptrAlarmable;
	AlarmableManager::ALARM_ID id;

};



#endif _AlarmDeregistrationCommand
