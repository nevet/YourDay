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
	//Executor pointer to handle dynamic binding
	Executor* exe;

	//Processing the raw input to formatted input
	lang.separate(input);
	//Get status from LanguageHandler
	fxStatus = lang.getStatus();

	//Check if raw input has been proceeded successfully
	if (!sh.error(fxStatus))
	{
		//no error occured, we should retrieve the packed executor
		exe = lang.pack(quit, generalEntryList, diduknowBoxList, &store);

		//exe is NULL pointer indicates EXIT command received
		if (exe != NULL)
		{
			//then we execute the executor and caught the exception threw by it
			exe->execute();
			fxStatus = exe->getStatus();

			//after the execusion, the executor should be destroyed to save memory
			delete exe;
		}
	}
}