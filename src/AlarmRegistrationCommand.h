// command for updating alarm registration 

#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "RegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public RegistrationCommand
{
public:

	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(Alarmable* cmd, AlarmableManager::ALARM_ID id);
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator =(const AlarmRegistrationCommand&) = delete;
	~AlarmRegistrationCommand() = default;

	void setTime(float t);

	void execute();

private:

	Alarmable* ptrAlarmable;
	float time; 
	AlarmableManager::ALARM_ID id;

};



#endif _AlarmRegistrationCommand
