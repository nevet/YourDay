#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H

#include "Signal.h"

using namespace std;

class StatusHandler
{
public:
	bool success(Signal signal);
	bool error(Signal signal);	
};

#endif