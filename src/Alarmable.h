// attribute that allows game object to have alarms

#ifndef _Alarmable
#define _Alarmable

enum class RegistrationState;
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;
#include "AlarmableManager.h"

class Alarmable
{

	friend class AlarmableAttorney;

public:

	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator =(const Alarmable&) = delete;
	~Alarmable();

	virtual void Alarm0(); // user defined 
	virtual void Alarm1();
	virtual void Alarm2();
	virtual void Alarm3();
	virtual void Alarm4();

	void SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float t);
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

private:

	struct RegistrationData
	{
		AlarmableManager::AlarmMapRef myDeleteRef;
		RegistrationState currentState;
		AlarmRegistrationCommand* pRegCmd;
		AlarmDeregistrationCommand* pDeregCmd;
	};

	RegistrationData RegData[AlarmableManager::ALARM_NUMBER]; // array of registration data for mutiple alarms 

	void SceneRegistration(AlarmableManager::ALARM_ID id, float t);
	void SceneDeregistration(AlarmableManager::ALARM_ID id);
	void SetDeleteRef(AlarmableManager::AlarmMapRef ref, AlarmableManager::ALARM_ID id);
	AlarmableManager::AlarmMapRef GetDeleteRef(AlarmableManager::ALARM_ID id);

	void TriggerAlarm(AlarmableManager::ALARM_ID id);

};


#endif _Alarmable
