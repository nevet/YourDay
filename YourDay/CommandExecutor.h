/**
* CommandExecutor is to be accessed in the FunctionHandler class
* CommandExecutor is used to manipulate the entry list passed in by the FunctionHandler class regarding
* to the type of command specified by FunctionHandler
* The types of command are:
*		Add		: add an entry to the event list
*		Delete	: delete an entry from the event list
*		Edit	: edit an entry in the event list
*		Search	: search for an entry containing a keyword in the event list
* It has a public API executeCommand to do the logic tasks to manipulate the entry list
* and the APIs to get and clear status signal
*/
#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Signal.h"
#include "LangHandler.h"

#define MAXIMUM_LENGTH 255

using namespace std;

class CommandExecutor
{
private:
	/**
	* Status signal of command executing process. Signal will be:
	* CLEAR		Testing signal;
	* SUCCESS	Success indicator, all process are successfully handled;
	* ERROR		Error indicator, some errors occured when executing.
	*/
	Signal CEStatus;

	void updateRaw(string* raw, string* updateDetails);

	/**
	* These private methods are to be called in executeCommand operation to
	* handle the corresponding tasks.
	*
	* 3 parameters may be passed:
	*
	* @param entryList
	*			is the pointer to the entry list vector
	* @param details
	*			is the encoded string contains the details to be added
	* @param matchedEntryList
	*			is the vector contains all matching results
	*
	* format for encoded string can be found in comments of LangHandler::encoded()
	*/
	void addEntry(vector<string> * entryList, string details);
	void deleteEntry(vector <string>* entryList, string details);
	void searchEntry(vector <string>* entryList, string details, vector <string>* matchedEntryList);
	void updateEntry(vector <string>* entryList, string details);

public:
	CommandExecutor();

	Signal getStatus();

	/**
	* This operation will clear the status signal to testing CLEAR signal 
	*/
	void clearStatus();

	/**
	* This operation is the main logic operation in CommandExecutor class
	* and will be called in the execute() operator inside FunctionHandler class
	* It executes user command, manipulating the entry list
	* It takes in 3 parameters passed by FunctionHandler class
	* @param entryList
	*				is the string vector pointer points to the list of events
	* @param type
	*				is the type of command, including:
	*					ADD_COMMAND		: add an entry to the event list
	*					DELETE_COMMAND	: delete an entry from the event list
	*					EDIT_COMMAND	: edit an entry in the event list
	*					SEARCH_COMMAND	: search for an entry containing a keyword in the event list
	* @param detail
	*				is the string to pass the command detail
	*
	*				For add command: it is the entry string to add to the event list
	*				For delete and update command: it is the string specify the keyword in the entry to be delete/update
	*				For search command: it is the key word to search in the event list
	*/
	void executeCommand(vector <string> * entryList, Signal type, string detail, vector<string>* result);

	~CommandExecutor();
};

#endif;