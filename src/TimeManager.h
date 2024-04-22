// singleton manager for handling total and frame time 

#ifndef _TimeManager
#define _TimeManager

class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;
private:

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager();

	static TimeManager* ptrInstance;

	static TimeManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new TimeManager();
		}
		return *ptrInstance;
	}

	// times 
	float currentTime;
	float frameTime;
	float previousTime;

	FreezeTime* pFreezeTime;

	void privDelete();
	float privGetFrameTime();
	float privGetTime();

	void privProcessTime();
	static void Terminate() { Instance().privDelete(); };

public:

	static float GetFrameTime() { return Instance().privGetFrameTime(); };
	static float GetTime() { return Instance().privGetTime(); };

};


#endif _TimeManager