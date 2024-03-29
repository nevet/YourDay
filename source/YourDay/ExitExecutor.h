#ifndef EXITEXECUTOR_H
#define EXITEXECUTOR_H

#include <vector>
#include "Executor.h"
#include "StorageHandler.h"

using namespace std;

class ExitExecutor : public Executor
{
private:
	vector<string>* _generalEntryList;
	vector<string>* _calendarEntryList;

	StorageHandler* _store;

	bool* _quit;

public:
	ExitExecutor(vector<string>* generalEntryList, 
				 vector<string>* calendarEntryList,
				 StorageHandler* store, bool* quit);

	void execute();
};

#endif