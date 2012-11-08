#ifndef UPDATEEXECUTOR_H
#define UPDATEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class UpdateExecutor : public Executor
{
private:
	vector<string>* _focusingEntryList;
	vector<string> _undoFocusingEntryList;

	string _details;

public:
	UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField);

	void execute();
	void undo();
};

#endif