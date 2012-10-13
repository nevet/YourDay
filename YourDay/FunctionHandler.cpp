#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	ram=new vector<string>(MAXIMUM_SIZE);
	StorageHandler store=new StorageHandler();
	store.readData(ram);
}

void FunctionHandler::excute(string* input,bool quit)
{
	LangHandler lang=new LangHandler();
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