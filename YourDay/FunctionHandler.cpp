#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler(vector<string>* generalEntryList,
								 vector<string>* calendarEntryList,
								 vector<string>* diduknowBoxList)
{
	generalEntryList->clear();
	calendarEntryList->clear();
	diduknowBoxList->clear();
	
	store.readData(generalEntryList);
}

void FunctionHandler::setStatus()
{
	status=fxStatus;
}

void FunctionHandler::execute(string input,
							  vector<string>* generalEntryList,
							  vector<string>* calendarEntryList,
							  vector<string>* diduknowBoxList)
{
	LangHandler lang;
	CommandExecutor command;

	Signal langSignal;
	Signal cmdSignal;

	string formatInput;

	//Processing the raw input to formatted input
	lang.separate(input);
	formatInput = lang.retrieve();
	
	//Get the commandType by the Singal;
	langSignal = lang.getStatus();
	fxStatus = langSignal;

	command.executeCommand(generalEntryList, langSignal, formatInput, diduknowBoxList);

	if (diduknowBoxList->size() != 0)
	{
		for (int i = 0; i < diduknowBoxList->size(); i++)
		{
			string decodedOutput;
			string temp = diduknowBoxList->at(i);
			decodedOutput = lang.decoder(temp);
			diduknowBoxList->at(i) = decodedOutput;
		}
	}

	fxStatus = command.getStatus();
	store.writeData(generalEntryList);

	setStatus();
}

void FunctionHandler::saveData(vector<string>* generalEntryList,
							   vector<string>* calendarEntryList,
							   vector<string>* diduknowBoxList)
{
	store.writeData(generalEntryList);
}