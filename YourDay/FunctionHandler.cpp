#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	ram.clear();
}

void FunctionHandler::setStatus()
{
	status = CLEAR;
}

void FunctionHandler::execute(string input, bool quit)
{
	LangHandler lang;
	CommandExecutor command=new CommandExecutor();
	string formatInput;
	
	lang.process(input,formatInput,cmd);

	switch()
	{
	case ADD:
		command.add();   
	case DELETE:
		command.del();
	}
}