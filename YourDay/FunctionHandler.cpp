#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler(vector<string>* generalEntryList,
								 vector<string>* calendarEntryList,
								 vector<string>* diduknowBoxList)
{
	//set default value for function handler status
	fxStatus = CLEAR;
	
	generalEntryList->clear();
	calendarEntryList->clear();
	diduknowBoxList->clear();
	
	store.readData(generalEntryList);
}

Signal FunctionHandler::getStatus()
{
	return fxStatus;
}

void FunctionHandler::clearStatus()
{
	fxStatus = CLEAR;
}

void FunctionHandler::execute(string input, bool* quit,
							  vector<string>* generalEntryList,
							  vector<string>* calendarEntryList,
							  vector<string>* diduknowBoxList)
{
	LangHandler lang;
	CommandExecutor command;

	Signal userCommand;

	string encodedInput;

	//Processing the raw input to formatted input
	lang.separate(input);
	//Get status from LanguageHandler
	fxStatus = lang.getStatus();

	//Check if raw input has been proceeded successfully
	if (!sh.error(fxStatus))
	{
		//no error occured, we should retrieve the proceeded results
		userCommand = lang.retrieveUserCommand();
		encodedInput = lang.retrieveEncodedInfo();

		//if user typed EXIT indicator, no more operations should be entertained
		if (userCommand = EXIT_COMMAND)
		{
			*quit = true;
			//safe exit
			fxStatus = SUCCESS;
		} else
		{
			command.executeCommand(generalEntryList, userCommand, encodedInput, diduknowBoxList);

			//keep track of Signals threw by CommandHandler
			fxStatus = command.getStatus();
			//after one iteration, command status should be cleared
			command.clearStatus();
		}
	}
}

void FunctionHandler::saveData(vector<string>* generalEntryList,
							   vector<string>* calendarEntryList,
							   vector<string>* diduknowBoxList)
{
	store.writeData(generalEntryList);
}