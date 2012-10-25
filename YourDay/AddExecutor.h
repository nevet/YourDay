#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class AddExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	string _details;

public:
	AddExecutor(vector<string>* calendarEntryList, vector<string>* generalEntryList, string details);

	void execute();
	void undo();
};

#endif