#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <iostream>
#include <vector>
#include "StorageHandler.h"
#include "Handler.h"
#include "LangHandler.h"
#include "CommandExecutor.h"
#include "StatusHandler.h"

#define MAXIMUM_SIZE 1000

/**
* FunctionHandler is the main handler in the logic component. Function handler
* knows LanguageHandler and CommandExecutor. FunctionHandler has only one public
* API execute() and should be called in the main(). FunctionHandler owns the
* copy of the file, which is a private vector of strings, and an instance of
* StorageHandler.
*/
class FunctionHandler: public Handler
{
private:
	StatusHandler sh;
	vector<string> ram;
	Signal fxStatus;
	//will be constructed when FunctionHandler constructed
	StorageHandler store;
public:
	/**
	* The instance of FunctionHandler should be created once and only once in
	* main().
	*/
	FunctionHandler();
	
	/**
	* Implement virtual setStatus(). Signal will be:
	* CLEAR		Testing signal;
	* SUCCESS	Success indicator, all process are successfully handled;
	* ERROR		Error indicator, some errors occured when executing.
	*/
	void setStatus();
	
	/**
	* The operation is periodically called in main(). It will handle the flow
	* of the logic component.
	*
	* @praram input
	*			is the user input took from the user and passed by UIHandler
	* @param quit
	*			is the indicator for terminating the whole program
	*/
	void execute(string input, bool quit, vector<string>* result);

	~FunctionHandler();
};
#endif