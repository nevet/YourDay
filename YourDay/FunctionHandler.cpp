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

void FunctionHandler::setStatus()
{
	status = fxStatus;
}

void FunctionHandler::execute(string input, bool* quit,
							  vector<string>* generalEntryList,
							  vector<string>* calendarEntryList,
							  vector<string>* diduknowBoxList)
{
	LangHandler lang;
	CommandExecutor command;

	Signal langStatus;
	Signal cmdSignal;
	Signal userCommand;

	string encodedInput;

	//Processing the raw input to formatted input
	lang.separate(input);
	//Get status from LanguageHandler
	langStatus = lang.getStatus();

	//Check if raw input has been proceeded successfully
	if (sh.error(langStatus))
	{
		//if not, FunctionHandler status should be set to langSignal
		fxStatus = langStatus;
	} else
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

			if (sh.success(fxStatus))
			{
				store.writeData(generalEntryList);
			}
		}
	}

	setStatus();
}

void FunctionHandler::saveData(vector<string>* generalEntryList,
							   vector<string>* calendarEntryList,
							   vector<string>* diduknowBoxList)
{
	store.writeData(generalEntryList);
}