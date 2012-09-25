#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include "Object.h";
#include "Handler.h";

class LangHandler : Handler
{
public :
	LangHandler();
	void seperate(Object);
	Object retrieve();

	~LangHandler();
protected :
	

};


#endif