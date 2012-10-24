#include "Executor.h"

Executor::Executor()
{
	status = CLEAR;
}

void Executor::execute()
{
}

Signal Executor::getStatus()
{
	return status;
}