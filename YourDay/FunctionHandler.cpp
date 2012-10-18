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

vector<string>* FunctionHandler::getEntryList()
{
	vector<string>* passer;
	passer=&ram;
	return passer;
}

void FunctionHandler::execute(string input, bool quit, vector<string>* result)
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


	command.executeCommand(passer,langSignal,formatInput, result);
	if (result ->size()!=0)
	{
		for (int i =0; i< result ->size(); i++)
		{
			string decodedOutput;
			string temp = result ->at(i);
			decodedOutput = lang.decoder(temp);
			result ->at(i) = decodedOutput;
		}
	}

	//fxStatus=command.getStatus();
	store.writeData(passer);

	setStatus();
}

