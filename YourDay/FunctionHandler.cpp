#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	ram=new vector<string>(MAXIMUM_SIZE);
	StorageHandler store=new StorageHandler();
	store.readFile(ram);
}

void FunctionHandler::excute(string input)
{
	LangHandler lang=new LangHandler();
	
}