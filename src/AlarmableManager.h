// manager for alarmable objects

#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>
class Alarmable;

//enum class ALARM_ID;

class AlarmableManager
{

public:
	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator = (const AlarmableManager&) = delete;
	~AlarmableManager();

	enum class ALARM_ID { ALARM_0, ALARM_1, ALARM_2, ALARM_3, ALARM_4 };


	void Deregister(Alarmable * obj, ALARM_ID);
	void ProcessAlarms();
	void Register(float t, Alarmable * obj, ALARM_ID);

	static const int ALARM_NUMBER = 5;

private:

	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	using AlarmMap = std::multimap<float, AlarmEvent>;
	AlarmMap alarmMap;

public:

	using AlarmMapRef = AlarmMap::iterator;

};



#endif _AlarmableManager
