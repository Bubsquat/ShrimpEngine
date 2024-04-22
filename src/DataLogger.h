// singleton dev tool for writing data to the screen 

#ifndef _DataLogger
#define _DataLogger

#include <queue>
class SpriteString;

class DataLogger
{
	friend class DataLoggerAttorney;
private:

	float InitialXPos; 
	float InitialYPos; 
	float currentYPos; 
	static char DebugBuff[256];

	using SpriteStringQueue = std::queue<SpriteString*>;
	SpriteStringQueue stringQueue;

	static DataLogger* ptrInstance;

	DataLogger();
	DataLogger(const DataLogger&) = delete;
	DataLogger& operator=(const DataLogger&) = delete;
	~DataLogger() = default;

	static DataLogger& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new DataLogger();
		}
		return *ptrInstance;
	}

	void privAdd(std::string s);
	void privSetDLPos(float posX, float posY);
	void privRender();
	void privDelete();

public:

	static void Add(char* c, ...)
	{
		// get input string
		va_list args;

		va_start(args, c);
		vsprintf_s(DebugBuff, c, args);
		va_end(args);

		std::string s(DebugBuff);
		
		Instance().privAdd(s); 
	};

	static void SetDLPos(float x, float y) { Instance().privSetDLPos(x, y); };
};



#endif _DataLogger

