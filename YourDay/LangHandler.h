#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include "DetailsObject.h"
#include "Handler.h";

class LangHandler : Handler
{
private:
	DetailsObject details;

public :
	LangHandler();

	void setStatus();
	void seperate(Object obj);

	DetailsObject* retrieve();

	~LangHandler();
protected :
	

};


#endif