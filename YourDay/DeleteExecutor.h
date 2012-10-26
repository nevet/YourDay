#ifndef DELETEEXECUTOR_H
#define DELETEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class DeleteExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	string _details;

public:
	DeleteExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details);

	void execute();
	void undo();
};

#endif