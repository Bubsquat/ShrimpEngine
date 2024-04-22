// attorney class for DataLogger dev tool 

#ifndef _DataLoggerAttorney
#define _DataLoggerAttorney

#include "DataLogger.h"

class DataLoggerAttorney
{
	friend class Game;

private:

	static void Terminate() { DataLogger::Instance().privDelete(); };
	static void Render() { DataLogger::Instance().privRender(); };

};

#endif _DataLoggerAttorney
