#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Signal.h"

class Executor
{
protected:
	Signal status;
public:
	Executor();

	virtual void execute();
	Signal getStatus();
};

#endif