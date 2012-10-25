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
	StorageHandler* _store;

	bool* _quit;

public:
	ExitExecutor(vector<string>* generalEntryList,
				 StorageHandler* store, bool* quit);

	void execute();
};

#endif