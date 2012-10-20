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

void FunctionHandler::execute(string input, bool* quit,
							  vector<string>* generalEntryList,
							  vector<string>* calendarEntryList,
							  vector<string>* diduknowBoxList)
{
	LangHandler lang;
	CommandExecutor command;

	Signal langSignal;
	Signal cmdSignal;
	Signal userCommand;

	string formattedInput;

	//Processing the raw input to formatted input
	lang.separate(input);
	//Get status from LanguageHandler
	langSignal = lang.getStatus();

	//Check if raw input has been proceeded successfully
	if (!sh.success(langSignal))
	{
		//if not, FunctionHandler status should be set to langSignal
		fxStatus = langSignal;
	} else
	{	
		userCommand = lang.retrieveUserCommand();
		formattedInput = lang.retrieveEncodedInfo();

		if (userCommand = EXIT_COMMAND)
		{
			*quit = true;
		} else
		{
			command.executeCommand(generalEntryList, userCommand, formattedInput, diduknowBoxList);

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
		}

		fxStatus = command.getStatus();
		if (sh.success(fxStatus))
		{
			store.writeData(generalEntryList);
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