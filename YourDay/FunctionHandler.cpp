#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	ram=new vector<string>(MAXIMUM_SIZE);
	StorageHandler store;//=new StorageHandler();
	store.readData(ram);
}

void FunctionHandler::excute(string* userInput,bool quit)
{
	LangHandler lang=new LangHandler();
	string* processedInput;
	Signal signal;

	lang.seperate(userInput);

	processedInput=lang.retrieve();

	signal=lang.getStatus();
	switch()
	{
	case ADD:
		  
	case DELETE:
		
	}

}