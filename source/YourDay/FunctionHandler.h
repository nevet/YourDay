#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <iostream>
#include <vector>
#include <stack>

#include "StorageHandler.h"
#include "Executor.h"
#include "Log.h"
#include "LangHandler.h"

#define MAXIMUM_SIZE 1000

/**
* FunctionHandler is the main handler in the logic component. Function handler
* knows LanguageHandler and CommandExecutor. FunctionHandler has only one public
* API execute() and should be called in the main(). FunctionHandler owns the
* copy of the file, which is a private vector of strings, and an instance of
* StorageHandler.
*
* @author A0091847U
*/
class FunctionHandler
{
private:
	Log log;

	//will be constructed when FunctionHandler constructed
	StorageHandler store;

	//stack for undo purpose
	stack<Executor*> undoStk;

public:
	/**
	* The constructor will initialize three lists and flush stored information
	* into corresponding list.
	*
	* The instance of FunctionHandler should be created once and only once in
	* main().
	*/
	FunctionHandler(vector<string>* generalEntryList,
					vector<string>* calendarEntryList,
					vector<string>* resultList) throw (string);
	
	/**
	* The operation is periodically called in main(). It will handle the flow
	* of the logic component.
	*
	* @praram input
	*			is the user input took from the user and passed by UIHandler
	* @param quit
	*			is the indicator for terminating the whole program
	*/
	void execute(string input, bool* quit, Signal focusingField,
				 vector<string>* generalEntryList,
				 vector<string>* calendarEntryList,
				 vector<string>* resultList);
};
#endif