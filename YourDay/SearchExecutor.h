#ifndef SEARCHEXECUTOR_H
#define SEARCHEXECUTOR_H

#include <vector>
#include <algorithm>
#include "Executor.h"

using namespace std;

class SearchExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _matchedEntryList;
	
	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	vector<string> _undoMatchedEntryList;

	string _details;

public:
	SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details);

	void execute();
	void undo();
};

#endif