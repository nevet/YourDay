#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include "DetailsObject.h"
#include "Handler.h";

class LangHandler : Handler
{
private:
	string* details;
	Command command;

public :
	enum Command {ADD, DELETE, UPDATE, SEARCH};
	LangHandler();

	void setStatus();
	void seperate(string* userInput, Command & command);

	void retrieve(string * details, Command command);

	~LangHandler();
};


#endif