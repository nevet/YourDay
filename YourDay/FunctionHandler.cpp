#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler()
{
	vector<string>* passer;
	passer=&ram;
	ram.clear();
	store.readData(passer);
}

FunctionHandler::~FunctionHandler()
{
	vector<string>* passer;
	passer=&ram;
	store.writeData(passer);
}

void FunctionHandler::setStatus()
{
	status=fxStatus;
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
	//Processing the raw input to formatted input
	lang.separate(input);
	formatInput=lang.retrieve();
	
	//Get the commandType by the Singal;
	langSignal=lang.getStatus();
	fxStatus=langSignal;


	command.executeCommand(passer,langSignal,formatInput);
	//fxStatus=command.getStatus();
	store.writeData(passer);

	setStatus();
}

