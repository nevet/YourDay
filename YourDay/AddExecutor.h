#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class AddExecutor : public Executor
{
private:
	vector<string>* _entryList;
	vector<string> _undoEntryList;

	string _details;

public:
	AddExecutor(vector<string>* entryList, string details);

	void execute();
	void undo();
};

#endif