#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <vector>
#include "Signal.h"

using namespace std;

class Command
{
private:
	vector <string*> * entryList;
	Signal status;
	
	void setStatus(Signal statusSignal);

	void addEntry(string*);
	void deleteEntry(string*);
	void searchEntry(string*);
	void updateEntry(string*);

public:
	Command();

	void getStatus();
	void clearStatus();

	void executeCommand(CommandType type, string*);

	~Command();
};

#endif;