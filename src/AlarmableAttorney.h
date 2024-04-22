// attorney for alarmable attribute 

#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
		friend class AlarmableManager;
	private:
		static void TriggerAlarm(Alarmable* obj, AlarmableManager::ALARM_ID id) { obj->TriggerAlarm(id); };
		static void SetDeleteRef(Alarmable* obj, AlarmableManager::AlarmMapRef ref, AlarmableManager::ALARM_ID id) { obj->SetDeleteRef(ref, id); };
		static AlarmableManager::AlarmMapRef GetDeleteRef(Alarmable* obj, AlarmableManager::ALARM_ID id) { return obj->GetDeleteRef(id); };
	};
public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
	private:
		static void SceneRegistration(Alarmable* obj, AlarmableManager::ALARM_ID id, float t) { obj->SceneRegistration(id, t); };
		static void SceneDeregistration(Alarmable* obj, AlarmableManager::ALARM_ID id) { obj->SceneDeregistration(id); };
	};
};




#endif _AlarmableAttorney
