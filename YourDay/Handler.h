#ifndef HANDLER_H
#define HANDLER_H

class Handler
{
protected:
	Signal status;

public:
	Handler();

	Signal getStatus() { return status; };
	virtual void setStatus() = 0;
}

#endif