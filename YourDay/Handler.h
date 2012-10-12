#ifndef HANDLER_H
#define HANDLER_H

#include "Signal.h"

class Handler
{
protected:
	Signal status;
public:
	Handler();

	Signal getStatus() { return status; };
	virtual void setStatus() = 0;

	~Handler();
};

#endif