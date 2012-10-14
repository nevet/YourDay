#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Signal.h"
#include "LangHandler.h"

using namespace std;

class CommandExecutor
{
private:
	Signal status;
	
	/**
	set the status signal of command execusion process

	@param status signal to be set to
	@return void
	*/
	void setStatus(Signal statusSignal);

	/**
	add an entry as a pure string to entry list string vector

	@param the entry string to be added
	@return void
	*/
	void addEntry(vector<string> * entryList, string eventDetails);

	void deleteEntry(vector <string>* entryList, string entry);
	void searchEntry(vector <string>* entryList, string keyWord);
	void updateEntry(vector <string>* entryList, string entry);

public:
	CommandExecutor();

	/**
	get the status signal of command execusion process

	@param void
	@return status signal of command execusion process
	*/
	Signal getStatus();

	/**
	clear the status of command execusion proces to default CLEAR signal

	@param void
	@return void
	*/
	void clearStatus();

	/**
	execute user command

	@param the entry list string vector, type signal of command, command detail string 
	@return void
	*/
	void executeCommand(vector <string> * entryList, Signal type, string detail);

	~CommandExecutor();
};

#endif;