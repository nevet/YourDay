#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Signal.h"

/**
* This class is used to do the execusion of corresponding command. Specific
* executor will derive from this super class. We can easily execute specific
* command by doing dynamic binding.
*/
class Executor
{
//we set status as protected variable so that subclass is able to make change
protected:
	Signal status;
public:
	/**
	* Note that different subclass may take in different parameter, so this
	* function should be overridden by its subclass.
	*/
	Executor();

	/**
	* This operation should be overwriten by its sub-class. The operation does
	* the execution of the command. Specific behaviour will be defined in
	* corresponding subclass.
	*/
	virtual void execute();
	Signal getStatus();
};

#endif