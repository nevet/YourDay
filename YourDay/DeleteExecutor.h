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
	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;

	string _details;

public:
	DeleteExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details);

	void execute();
	void undo();
};

#endif