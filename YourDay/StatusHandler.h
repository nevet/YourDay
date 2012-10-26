#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H

#include <string>
#include "Signal.h"

using namespace std;

class StatusHandler
{
private:
	//These are successful display message and will be used in intepreteSignal operation to get the feedback message string
	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	//These are error feedback messages on user input and will be used in intepreteSignal operation to get the feedback message string
	static const string COMMAND_ERROR_MESSAGE;
	static const string LENGTH_EXCEED_ERROR_MESSAGE;
	static const string LENGTH_ZERO_ERROR_MESSAGE;
	static const string INDEX_ERROR_MESSAGE;
	static const string INVALID_DATE_ERROR_MESSAGE;
	static const string INVALID_TIME_ERROR_MESSAGE;
	static const string UNDO_ERROR_MESSAGE;

	//These are error messages on displaying UI and will be used in intepreteSignal operation to get the feedback message string
	static const string DISPLAY_ERROR_MESSAGE;

	//These are error messages on executing commands and will be used in intepreteSignal operation to get the feedback message string
	static const string NULL_EXECUTOR_ERROR_MESSAGE;
	static const string ADD_FAILED_MESSAGE;
	static const string DELETE_FAILED_MESSAGE;
	static const string SEARCH_FAILED_MESSAGE;
	static const string UPDATE_FAILED_MESSAGE;
public:

	string interpreteSignal(Signal outSignal);
	bool success(Signal signal);
	bool error(Signal signal);	
};

#endif