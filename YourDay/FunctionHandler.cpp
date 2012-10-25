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

	while (!undoStk.empty())
	{
		undoStk.pop();
	}
	
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

	//clear diduknow box list to keep information updated
	diduknowBoxList->clear();

	//Processing the raw input to formatted input
	lang.separate(input);
	//Get status from LanguageHandler
	fxStatus = lang.getStatus();

	//Check if raw input has been proceeded successfully
	if (!sh.error(fxStatus))
	{
		//no error occured, we should retrieve the packed executor
		exe = lang.pack(quit, generalEntryList, diduknowBoxList, &store);

		//exe is NULL means undo command encountered
		if (exe != NULL)
		{
			//then we execute the executor and caught the exception threw by it
			exe->execute();
			fxStatus = exe->getStatus();
			
			undoStk.push(exe);
		} else
		{
			//if undo stack is empty, undo should be prevented
			if (undoStk.empty())
			{
				fxStatus = UNDO_E;
			}
			else
			{
				exe = undoStk.top();
				exe->undo();

				//and then delete the pointer to free the memory
				undoStk.pop();
				delete exe;
			}
		}
	}
}