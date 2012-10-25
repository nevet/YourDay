#ifndef DELETEEXECUTOR_H
#define DELETEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class DeleteExecutor : public Executor
{
private:
	vector<string>* _entryList;
	vector<string> _undoEntryList;

	string _details;

public:
	DeleteExecutor(vector<string>* entryList, string details);

	void execute();
	void undo();
};

#endif