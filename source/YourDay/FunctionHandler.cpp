#include <cassert>

#include "FunctionHandler.h"

using namespace std;

FunctionHandler::FunctionHandler(vector<string>* generalEntryList,
								 vector<string>* calendarEntryList,
								 vector<string>* diduknowBoxList) 
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(diduknowBoxList!=NULL);

	//set default value for function handler status
	fxStatus = CLEAR;
	
	//generalEntryList->clear();
	//calendarEntryList->clear();
	//diduknowBoxList->clear();

	while (!undoStk.empty())
	{
		undoStk.pop();
	}

	store.readData(generalEntryList, calendarEntryList);
}

Signal FunctionHandler::getStatus()
{
	return fxStatus;
}

void FunctionHandler::clearStatus()
{
	fxStatus = CLEAR;
}

void FunctionHandler::execute(string input, bool* quit, Signal focusingField,
							  vector<string>* generalEntryList,
							  vector<string>* calendarEntryList,
							  vector<string>* diduknowBoxList) throw (string)
{
	//log.write("logic component entered.");
	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(diduknowBoxList!=NULL);

	LangHandler lang;
	//log.writeCreated("Language Handler");
	//Executor pointer to handle dynamic binding
	Executor* exe;
	//log.writeCreated("Executor pointer");

	//clear diduknow box list to keep information updated
	diduknowBoxList->clear();

	try
	{
		//Processing the raw input to formatted input
		lang.separate(input);
		//log.writeExecuted("LangHandler::separate()");

		//no error occured, we should retrieve the packed executor
		exe = lang.pack(quit, focusingField, generalEntryList, calendarEntryList, diduknowBoxList, &store);
		//log.writeExecuted("LangHandler::separate()");

		//exe is NULL means undo command encountered
		if (exe != NULL)
		{
			//log.writeConditionEntered("exe != NULL", true);
			//then we execute the executor and caught the exception threw by it
			exe->execute();
			//log.writeExecuted("Executor::execute()");
			
			undoStk.push(exe);
			//log.writeExecuted("stack::push()");
		} else
		{
			//log.writeConditionEntered("exe != NULL", false);
			//if undo stack is empty, undo should be prevented
			if (undoStk.empty())
			{
				//log.writeConditionEntered("undoStk is empty", true);
				
				throw string ("Undo error\n");
			}
			else
			{
				//log.writeConditionEntered("undoStk is empty", false);
				
				exe = undoStk.top();
				exe->undo();
				//log.writeExecuted("Executor::undo()");

				//and then delete the pointer to free the memory
				undoStk.pop();
				//log.writeExecuted("stack::pop()");
				
				delete exe;
				//log.writeExecuted("delete exe");
			}
		}
	}
	catch (string excpt)
	{
		throw string (excpt);
	}
}