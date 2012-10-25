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
							  vector<string>* diduknowBoxList) throw (string)
{
	LangHandler lang;
	//Executor pointer to handle dynamic binding
	Executor* exe;

	//clear diduknow box list to keep information updated
	diduknowBoxList->clear();

	try
	{
		//Processing the raw input to formatted input
		lang.separate(input);

		//no error occured, we should retrieve the packed executor
		exe = lang.pack(quit, calendarEntryList, generalEntryList, diduknowBoxList, &store);

		//exe is NULL means undo command encountered
		if (exe != NULL)
		{
			//then we execute the executor and caught the exception threw by it
			exe->execute();
			undoStk.push(exe);
		} else
		{
			//if undo stack is empty, undo should be prevented
			if (undoStk.empty())
			{
				throw string ("Undo error\n");
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
	catch (string excpt)
	{
		throw string (excpt);
	}
}