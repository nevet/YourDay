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
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details) throw (string);

	void execute();
	void undo();
};

#endif