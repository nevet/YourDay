#ifndef DELETEEXECUTOR_H
#define DELETEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;
//author A0091734A
class DeleteExecutor : public Executor
{
private:
	vector<string>* _focusingEntryList;
	vector<string> _undoFocusingEntryList;

	string _details;

public:
	DeleteExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField);

	void execute();
	void undo();
};

#endif