#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;
//@author A0091734A
class AddExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _resultList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	int extractDay(string date);
	int extractMonth(string date);
	int extractYear(string date);

	bool isEarlier(string &entry1, string &entry2);
	string _details;

	
	int searchIndex(vector<string>* _entryList, string input);
	int binarySearch(vector<string>* _entryList, string key, int imin, int imax);
	void addToPosition(vector<string>* _entryList, int position, string input);


public:
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList, string details);

	void execute() throw (string);
	void undo();
};

#endif