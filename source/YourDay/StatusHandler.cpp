#include "StatusHandler.h"

bool StatusHandler::success(Signal signal)
{
	bool flag;
	
	if ((signal & MASK) == SUCCESS)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}

	return flag;
}

bool StatusHandler::error(Signal signal)
{
	bool flag;

	if ((signal & MASK) == ERR)
	{
		flag = true;
	} else
	{
		flag = false;
	}

	return flag;
}