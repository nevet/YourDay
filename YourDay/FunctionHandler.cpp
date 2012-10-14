#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	StorageHandler store;
	vector<string>* passer;
	passer=&ram;
	ram.clear();
	store.readData(passer);
}

void FunctionHandler::setStatus()
{
	status = CLEAR;
}

void FunctionHandler::execute(string input, bool quit)
{
	LangHandler lang;
	CommandExecutor command;
	Signal langSignal;
	Signal cmdSignal;
	string formatInput;
	vector<string> *passer;
	passer=&ram;

	lang.seperate(input);
	formatInput=lang.retrieve();
	langSignal=lang.getStatus();

	command.executeCommand(passer,langSignal,formatInput);
	cmdSignal=command.getStatus();


}