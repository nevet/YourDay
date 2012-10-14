#include "StatusHandler.h"
//comitt
bool StatusHandler::success(Signal signal)
{
	bool flag;
	
	if (signal & Signal::MASK == Signal::SUCCESS)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}

	return flag;
}